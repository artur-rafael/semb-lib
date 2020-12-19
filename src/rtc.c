#include "rtc.h"

/***************************** Global Variables *****************************/

/*************************** Functions Signatures ***************************/

/****************************************************************************/
/********************************* Functions ********************************/
/****************************************************************************/

void RTC_Init(void) {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_HIBERNATE);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_HIBERNATE));

    HibernateEnableExpClk(SysCtlClockGet());
    HibernateClockConfig(HIBERNATE_OSC_LOWDRIVE);

    HibernateRTCSet(0);
    HibernateRTCTrimSet(0x7FFF);
    HibernateRTCEnable();
} /* RTC_Init() */

void RTC_SetDateAndTime(struct tm * dtTm) {
    RTC_SetSeconds(mktime(dtTm));
} /* RTC_SetTime() */

struct tm * RTC_GetDateAndTime(void) {
    time_t secs = HibernateRTCGet();
    return localtime(&secs);
} /* RTC_GetTime() */

void RTC_SetSeconds(time_t seconds) {
    HibernateRTCSet(seconds);
} /* RTC_SetSeconds() */

time_t RTC_GetSeconds(void) {
    return (time_t) HibernateRTCGet();
} /* RTC_GetSeconds() */

/****************************************************************************/
/***************************** Static Functions *****************************/
/****************************************************************************/
