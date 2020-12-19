#ifndef __LED_H__
#define __LED_H__

#include <stdbool.h>
#include <stdint.h>

#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

#define LED_BASE    GPIO_PORTF_BASE
#define LED_RED     GPIO_PIN_1
#define LED_BLUE    GPIO_PIN_2
#define LED_GREEN   GPIO_PIN_3

typedef enum {
    OFF = 0,
    RED = 0x2,
    BLUE = 0x4,
    GREEN = 0x8,
    YELLOW = 0xA,
    AQUA = 0xC,
    WHITE = 0xE
} LED_Color;

void LED_Init(void);
void LED_SetColor(LED_Color color);
LED_Color LED_GetColor(void);

#endif /* __LED_H__ */
