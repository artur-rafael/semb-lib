#include "led.h"

/****************************************************************************/
/********************************* Functions ********************************/
/****************************************************************************/

void LED_Init(void) {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF));

    GPIOPinTypeGPIOOutput(LED_BASE, LED_RED | LED_BLUE | LED_GREEN);
    LED_SetColor(OFF);
} /* LED_Init() */

void LED_SetColor(LED_Color color) {
    GPIOPinWrite(LED_BASE, LED_RED | LED_BLUE | LED_GREEN, color);
} /* LED_SetColor() */

LED_Color LED_GetColor(void) {
    return (LED_Color) GPIOPinRead(LED_BASE, LED_RED | LED_BLUE | LED_GREEN);
} /* LED_GetColor() */

