#include "keypad.h"

/***************************** Global Variables *****************************/

static char keypad[KEYPAD_LINES][KEYPAD_COLUMNS] = { {'1', '2', '3', 'F'},
                                                     {'4', '5', '6', 'E'},
                                                     {'7', '8', '9', 'D'},
                                                     {'A', '0', 'B', 'C'}
                                                   };

static KEYPAD_State keypadStates[KEYPAD_LINES][KEYPAD_COLUMNS] = { {KEY_IDLE, 0} };
static uint32_t lineStartBase[KEYPAD_LINES] = {KEYPAD_1_BASE, KEYPAD_4_BASE, KEYPAD_7_BASE, KEYPAD_A_BASE};

static uint8_t linePins[KEYPAD_LINES] = {KEYPAD_Y1, KEYPAD_Y2, KEYPAD_Y3, KEYPAD_Y4};
static uint8_t columnPins[KEYPAD_COLUMNS] = {KEYPAD_X1, KEYPAD_X2, KEYPAD_X3, KEYPAD_X4};

/*************************** Functions Signatures ***************************/

uint32_t xWaitElapsed(uint32_t time);

static uint32_t KEYPAD_CheckKeyState(uint8_t line, uint8_t column);
static bool KEYPAD_IsKeyPressed(uint8_t line, uint8_t column);

/****************************************************************************/
/********************************* Functions ********************************/
/****************************************************************************/

void KEYPAD_Init(void) {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB));

    GPIOPinTypeGPIOOutput(KEYPAD_BASE, KEYPAD_Y1 | KEYPAD_Y2 | KEYPAD_Y3 | KEYPAD_Y4);
    GPIOPinWrite(KEYPAD_BASE, KEYPAD_Y1 | KEYPAD_Y2 | KEYPAD_Y3 | KEYPAD_Y4, 0);

    GPIOPinTypeGPIOInput(KEYPAD_BASE, KEYPAD_X1 | KEYPAD_X2 | KEYPAD_X3 | KEYPAD_X4);
} /* KEYPAD_Init() */

uint8_t KEYPAD_Hit(void) {
    uint8_t row, column, key = 0;
    bool found = false;

    for(row = 0; row < KEYPAD_LINES && !found; row++) {
        for(column = 0; column < KEYPAD_COLUMNS && !found; column++) {
            if(KEYPAD_IsKeyPressed(row, column)) {
                key = (uint8_t) keypad[row][column];
                found = true;
            }
        }
    }

    return key;
} /* KEYPAD_Hit() */

char KEYPAD_Read(void) {
    uint8_t key = 0;
    while((key = KEYPAD_Hit()) == 0);
    return (char) key;
} /* KEYPAD_Read() */

uint32_t KEYPAD_KeyEvent(void) {
    uint32_t event;

    for(uint32_t line = 0; line < KEYPAD_LINES; line++) {
        for(uint32_t column = 0; column < KEYPAD_COLUMNS; column++) {
            if((event = KEYPAD_CheckKeyState(line, column)) != KEYPAD_NO_EVENT)
                return event;
        }
    }

    return KEYPAD_NO_EVENT;
} /* KEYPAD_Events() */

/****************************************************************************/
/***************************** Static Functions *****************************/
/****************************************************************************/

static uint32_t KEYPAD_CheckKeyState(uint8_t line, uint8_t column) {
    uint32_t keyBase = lineStartBase[line] << column;
    bool isPressed = KEYPAD_IsKeyPressed(line, column);
    uint32_t time = xWaitElapsed(0);

    KEYPAD_State * key = &keypadStates[line][column];

    switch(key->state) {
        case KEY_IDLE:
            if(!isPressed)
                break;
            key->state = KEY_PRESS;
            key->timestamp = time;
            return keyBase + KEYPAD_STATE_PRESS;
        case KEY_PRESS:
            if(!isPressed) {
                key->state = KEY_RELEASE;
                return keyBase + KEYPAD_STATE_RELEASE;
            } else if(xWaitElapsed(key->timestamp) >= KEYPAD_THRESHOLD_TIME) {
                key->state = KEY_HOLD;
                return keyBase + KEYPAD_STATE_HOLD;
            }
            break;
        case KEY_RELEASE:
            key->state = KEY_IDLE;
            key->timestamp = 0;
            break;
        case KEY_HOLD:
            if(!isPressed) {
                key->state = KEY_RELEASE;
                return keyBase + KEYPAD_STATE_RELEASE;
            }
            break;
        default:
            break;
    }

    return KEYPAD_NO_EVENT;
} /* KEYPAD_CheckKeyState() */

static bool KEYPAD_IsKeyPressed(uint8_t line, uint8_t column) {
    GPIOPinWrite(KEYPAD_BASE, linePins[line], linePins[line]);
    uint32_t value = GPIOPinRead(KEYPAD_BASE, columnPins[column]);
    GPIOPinWrite(KEYPAD_BASE, linePins[line], 0);
    return value != 0;
} /* KEYPAD_ReadKeyValue() */
