#ifndef __WAIT_H__
#define __WAIT_H__

#include <stdbool.h>
#include <stdint.h>

#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/rom.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"

void WAIT_Timer0AInit(void);
void WAIT_Init(void);
void WAIT_TimerAInit(void);
void WAIT_Ms(int time);
uint32_t WAIT_Elapsed(uint32_t time);
void WAIT_ChronoMicro(uint32_t wait);
void WAIT_SysTickHandler(void);

#endif /* __WAIT_H__*/
