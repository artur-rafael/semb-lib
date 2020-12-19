#ifndef __RTC_H__
#define __RTC_H__

#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#include "driverlib/sysctl.h"
#include "driverlib/hibernate.h"

void RTC_Init(void);

void RTC_SetDateAndTime(struct tm * dtTm);
struct tm * RTC_GetDateAndTime(void);

void RTC_SetSeconds(time_t seconds);
time_t RTC_GetSeconds(void);

#endif /* __RTC_H__ */
