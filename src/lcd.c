#include "lcd.h"

/***************************** Global Variables *****************************/

static uint8_t displayCursorBlink = LCD_DISPLAY_CURSOR_BLINK_BASE;

/*************************** Functions Signatures ***************************/
extern void xWaitMs(uint32_t time);
extern void xWaitMicro(uint32_t wait);
extern void * xMalloc(size_t size);
extern void xFree(void * ptr);

static void LCD_Write(LCD_ModeSize mode, LCD_Type type, uint8_t bits);
static void LCD_Write4Bits(uint8_t bits);
static void LCD_Write8Bits(uint8_t bits);

/****************************************************************************/
/********************************* Functions ********************************/
/****************************************************************************/

void LCD_Init(void) {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA));
    GPIOPinTypeGPIOOutput(LCD_PORT, LCD_DB_PINS | LCD_RS_PIN | LCD_ENABLE_PIN);

    xWaitMs(16);
    LCD_Write(MODE_4, INSTRUCTION, 0b0011);
    xWaitMs(5);
    LCD_Write(MODE_4, INSTRUCTION, 0b0011);
    xWaitMicro(101);
    LCD_Write(MODE_4, INSTRUCTION, 0b0011);
    LCD_Write(MODE_4, INSTRUCTION, 0b0010);

    xWaitMs(11); // this must stay, idk why, otherwise it wont work

    LCD_Write(MODE_8, INSTRUCTION, LCD_FUNCTION_SET);
    LCD_Display(DISPLAY_ON);
    LCD_Clear();
    LCD_Write(MODE_8, INSTRUCTION, LCD_ENTRY_MODE_SET);

    xWaitMs(11); // this must stay, idk why, otherwise it wont work

} /* LCD_Init() */

void LCD_WriteChar(char ch) {
    LCD_Write(MODE_8, DATA, (uint8_t) ch);
} /* LCD_WriteChar() */

void LCD_WriteString(char * str) {
    //for(uint32_t i = 0; i < strlen(str); i++)
    for(uint32_t i = 0; i < ustrlen(str); i++)
        LCD_Write(MODE_8, DATA, (uint8_t) str[i]);
} /* LCD_WriteString() */

void LCD_Printf(char * fmt, ...) {
    va_list arg;
    va_start(arg, fmt);

    //char * buffer = xMalloc(strlen(fmt) + 1);
    char * buffer = xMalloc(LCD_DISPLAY_SIZE);

    //vsprintf(buffer, fmt, arg);
    uvsnprintf(buffer, LCD_DISPLAY_SIZE + 1, fmt, arg);

    LCD_WriteString(buffer);

    va_end(arg);
    xFree(buffer);
} /* LCD_Printf() */

void LCD_CenteredPrintf(char * fmt, ...) {
    va_list arg;
    va_start(arg, fmt);

    char * buffer = xMalloc(LCD_DISPLAY_SIZE);
    uvsnprintf(buffer, LCD_DISPLAY_SIZE, fmt, arg);

    LCD_SetCursor((uint8_t) (LCD_DISPLAY_SIZE - ustrlen(buffer))/2);
    LCD_WriteString(buffer);

    va_end(arg);
    xFree(buffer);
} /* LCD_CenteredPrintf() */

void LCD_Clear(void) {
    LCD_Write(MODE_8, INSTRUCTION, LCD_CLEAR_DISPLAY);
    xWaitMs(2);
} /* LCD_Clear() */

void LCD_Home(void) {
    LCD_Write(MODE_8, INSTRUCTION, LCD_RETURN_HOME);
    xWaitMs(2);
} /* LCD_Home() */

void LCD_Display(LCD_DisplayState display) {
    if(display == DISPLAY_ON)
        displayCursorBlink |= DISPLAY_ON;
    else
        displayCursorBlink &= DISPLAY_OFF;

    LCD_Write(MODE_8, INSTRUCTION, displayCursorBlink);
} /* LCD_Display() */

void LCD_Cursor(LCD_CursorState cursor) {
    if(cursor == CURSOR_ON)
        displayCursorBlink |= CURSOR_ON;
    else
        displayCursorBlink &= CURSOR_OFF;

    LCD_Write(MODE_8, INSTRUCTION, displayCursorBlink);
} /* LCD_Cursor() */

void LCD_Blink(LCD_BlinkState blink) {
    if(blink == BLINK_ON)
        displayCursorBlink |= BLINK_ON;
    else
        displayCursorBlink &= BLINK_OFF;

    LCD_Write(MODE_8, INSTRUCTION, displayCursorBlink);
} /* LCD_Blink() */

void LCD_SetCursor(uint8_t ddram) {
    if(ddram > 19)
        ddram = 19;
    LCD_Write(MODE_8, INSTRUCTION, LCD_SET_DDRAM_ADDR_BASE | ddram);
} /* LCD_SetCursor() */

/****************************************************************************/
/***************************** Static Functions *****************************/
/****************************************************************************/

static void LCD_Write(LCD_ModeSize mode, LCD_Type type, uint8_t bits) {
    GPIOPinWrite(LCD_PORT, LCD_RS_PIN, type << RS_SHIFT);
    if(mode == MODE_4)
        LCD_Write4Bits(bits);
    else
        LCD_Write8Bits(bits);
} /* LCD_Write() */

static void LCD_Write8Bits(uint8_t bits) {
    LCD_Write4Bits(bits >> 4);
    LCD_Write4Bits(bits);
    xWaitMicro(39);
} /* LCD_Write8Bits() */

static void LCD_Write4Bits(uint8_t bits) {
    GPIOPinWrite(LCD_PORT, LCD_ENABLE_PIN, 1 << ENABLE_SHIFT);
    GPIOPinWrite(LCD_PORT, LCD_DB_PINS, bits << DB_SHIFT);
    GPIOPinWrite(LCD_PORT, LCD_ENABLE_PIN, 0 << ENABLE_SHIFT);
} /* LCD_Write4Bits() */
