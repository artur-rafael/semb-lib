#include "wait.h"

/***************************** Global Variables *****************************/

volatile uint32_t __ms__;

/****************************************************************************/
/********************************* Functions ********************************/
/****************************************************************************/

void WAIT_Timer0AInit(void) {
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER0);
//    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_WTIMER0));
//
//    TimerConfigure(WTIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_ONE_SHOT);
//    TimerPrescaleSet(WTIMER0_BASE, TIMER_A, SysCtlClockGet()/1000000);
} /* WAIT_Timer0AInit() */

void WAIT_Init(void) {
    SysTickPeriodSet(SysCtlClockGet()/1000);
    SysTickIntEnable();
    SysTickEnable();
    WAIT_Timer0AInit();
}/* WAIT_Init() */

void WAIT_Ms(int time) {
    uint32_t start = __ms__;
    while((__ms__ - start) < time);
} /* WAIT_Ms() */

uint32_t WAIT_Elapsed(uint32_t time) {
    return __ms__ - time;
} /* WAIT_Elapsed() */

void WAIT_ChronoMicro(uint32_t wait) {
//    TimerLoadSet(WTIMER0_BASE, TIMER_A, wait);
//    TimerEnable(WTIMER0_BASE, TIMER_A);
//
//    while(TimerValueGet(WTIMER0_BASE, TIMER_A) != 0);
//
//    TimerDisable(WTIMER0_BASE, TIMER_A);
    SysCtlDelay(wait * (SysCtlClockGet() / 3 / 1000000));
} /* WAIT_ChronoMicro() */

void WAIT_SysTickHandler(void) {
    ++__ms__;
} /* WAIT_SysTickHandler() */
