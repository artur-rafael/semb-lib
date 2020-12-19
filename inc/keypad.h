#ifndef __KEYPAD_H__
#define __KEYPAD_H__

#include <stdbool.h>
#include <stdint.h>

#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/gpio.h"

typedef enum {
    KEY_IDLE,
    KEY_PRESS,
    KEY_RELEASE,
    KEY_HOLD
} KEYPAD_Event;

typedef struct {
    KEYPAD_Event state;
    uint32_t timestamp;
} KEYPAD_State;

#define KEYPAD_LINES            4
#define KEYPAD_COLUMNS          4

#define KEYPAD_BASE             GPIO_PORTB_BASE

#define KEYPAD_Y1               GPIO_PIN_0
#define KEYPAD_Y2               GPIO_PIN_1
#define KEYPAD_Y3               GPIO_PIN_2
#define KEYPAD_Y4               GPIO_PIN_3

#define KEYPAD_X1               GPIO_PIN_4
#define KEYPAD_X2               GPIO_PIN_5
#define KEYPAD_X3               GPIO_PIN_6
#define KEYPAD_X4               GPIO_PIN_7

#define KEYPAD_THRESHOLD_TIME   1500


#define KEYPAD_NO_EVENT         0

#define KEYPAD_STATE_PRESS      1
#define KEYPAD_STATE_RELEASE    2
#define KEYPAD_STATE_HOLD       4

#define KEYPAD_1_BASE           0x100
#define KEYPAD_1_PRESS          (KEYPAD_1_BASE + KEYPAD_STATE_PRESS)
#define KEYPAD_1_RELEASE        (KEYPAD_1_BASE + KEYPAD_STATE_RELEASE)
#define KEYPAD_1_HOLD           (KEYPAD_1_BASE + KEYPAD_STATE_HOLD)

#define KEYPAD_2_BASE           (KEYPAD_1_BASE << 1)
#define KEYPAD_2_PRESS          (KEYPAD_2_BASE + KEYPAD_STATE_PRESS)
#define KEYPAD_2_RELEASE        (KEYPAD_2_BASE + KEYPAD_STATE_RELEASE)
#define KEYPAD_2_HOLD           (KEYPAD_2_BASE + KEYPAD_STATE_HOLD)

#define KEYPAD_3_BASE           (KEYPAD_2_BASE << 1)
#define KEYPAD_3_PRESS          (KEYPAD_3_BASE + KEYPAD_STATE_PRESS)
#define KEYPAD_3_RELEASE        (KEYPAD_3_BASE + KEYPAD_STATE_RELEASE)
#define KEYPAD_3_HOLD           (KEYPAD_3_BASE + KEYPAD_STATE_HOLD)

#define KEYPAD_F_BASE           (KEYPAD_3_BASE << 1)
#define KEYPAD_F_PRESS          (KEYPAD_F_BASE + KEYPAD_STATE_PRESS)
#define KEYPAD_F_RELEASE        (KEYPAD_F_BASE + KEYPAD_STATE_RELEASE)
#define KEYPAD_F_HOLD           (KEYPAD_F_BASE + KEYPAD_STATE_HOLD)

#define KEYPAD_4_BASE           (KEYPAD_F_BASE << 1)
#define KEYPAD_4_PRESS          (KEYPAD_4_BASE + KEYPAD_STATE_PRESS)
#define KEYPAD_4_RELEASE        (KEYPAD_4_BASE + KEYPAD_STATE_RELEASE)
#define KEYPAD_4_HOLD           (KEYPAD_4_BASE + KEYPAD_STATE_HOLD)

#define KEYPAD_5_BASE           (KEYPAD_4_BASE << 1)
#define KEYPAD_5_PRESS          (KEYPAD_5_BASE + KEYPAD_STATE_PRESS)
#define KEYPAD_5_RELEASE        (KEYPAD_5_BASE + KEYPAD_STATE_RELEASE)
#define KEYPAD_5_HOLD           (KEYPAD_5_BASE + KEYPAD_STATE_HOLD)

#define KEYPAD_5_BASE           (KEYPAD_4_BASE << 1)
#define KEYPAD_5_PRESS          (KEYPAD_5_BASE + KEYPAD_STATE_PRESS)
#define KEYPAD_5_RELEASE        (KEYPAD_5_BASE + KEYPAD_STATE_RELEASE)
#define KEYPAD_5_HOLD           (KEYPAD_5_BASE + KEYPAD_STATE_HOLD)

#define KEYPAD_6_BASE           (KEYPAD_5_BASE << 1)
#define KEYPAD_6_PRESS          (KEYPAD_6_BASE + KEYPAD_STATE_PRESS)
#define KEYPAD_6_RELEASE        (KEYPAD_6_BASE + KEYPAD_STATE_RELEASE)
#define KEYPAD_6_HOLD           (KEYPAD_6_BASE + KEYPAD_STATE_HOLD)

#define KEYPAD_E_BASE           (KEYPAD_6_BASE << 1)
#define KEYPAD_E_PRESS          (KEYPAD_E_BASE + KEYPAD_STATE_PRESS)
#define KEYPAD_E_RELEASE        (KEYPAD_E_BASE + KEYPAD_STATE_RELEASE)
#define KEYPAD_E_HOLD           (KEYPAD_E_BASE + KEYPAD_STATE_HOLD)

#define KEYPAD_7_BASE           (KEYPAD_E_BASE << 1)
#define KEYPAD_7_PRESS          (KEYPAD_7_BASE + KEYPAD_STATE_PRESS)
#define KEYPAD_7_RELEASE        (KEYPAD_7_BASE + KEYPAD_STATE_RELEASE)
#define KEYPAD_7_HOLD           (KEYPAD_7_BASE + KEYPAD_STATE_HOLD)

#define KEYPAD_8_BASE           (KEYPAD_7_BASE << 1)
#define KEYPAD_8_PRESS          (KEYPAD_8_BASE + KEYPAD_STATE_PRESS)
#define KEYPAD_8_RELEASE        (KEYPAD_8_BASE + KEYPAD_STATE_RELEASE)
#define KEYPAD_8_HOLD           (KEYPAD_8_BASE + KEYPAD_STATE_HOLD)

#define KEYPAD_9_BASE           (KEYPAD_8_BASE << 1)
#define KEYPAD_9_PRESS          (KEYPAD_9_BASE + KEYPAD_STATE_PRESS)
#define KEYPAD_9_RELEASE        (KEYPAD_9_BASE + KEYPAD_STATE_RELEASE)
#define KEYPAD_9_HOLD           (KEYPAD_9_BASE + KEYPAD_STATE_HOLD)

#define KEYPAD_D_BASE           (KEYPAD_9_BASE << 1)
#define KEYPAD_D_PRESS          (KEYPAD_D_BASE + KEYPAD_STATE_PRESS)
#define KEYPAD_D_RELEASE        (KEYPAD_D_BASE + KEYPAD_STATE_RELEASE)
#define KEYPAD_D_HOLD           (KEYPAD_D_BASE + KEYPAD_STATE_HOLD)

#define KEYPAD_A_BASE           (KEYPAD_D_BASE << 1)
#define KEYPAD_A_PRESS          (KEYPAD_A_BASE + KEYPAD_STATE_PRESS)
#define KEYPAD_A_RELEASE        (KEYPAD_A_BASE + KEYPAD_STATE_RELEASE)
#define KEYPAD_A_HOLD           (KEYPAD_A_BASE + KEYPAD_STATE_HOLD)

#define KEYPAD_0_BASE           (KEYPAD_A_BASE << 1)
#define KEYPAD_0_PRESS          (KEYPAD_0_BASE + KEYPAD_STATE_PRESS)
#define KEYPAD_0_RELEASE        (KEYPAD_0_BASE + KEYPAD_STATE_RELEASE)
#define KEYPAD_0_HOLD           (KEYPAD_0_BASE + KEYPAD_STATE_HOLD)

#define KEYPAD_B_BASE           (KEYPAD_0_BASE << 1)
#define KEYPAD_B_PRESS          (KEYPAD_B_BASE + KEYPAD_STATE_PRESS)
#define KEYPAD_B_RELEASE        (KEYPAD_B_BASE + KEYPAD_STATE_RELEASE)
#define KEYPAD_B_HOLD           (KEYPAD_B_BASE + KEYPAD_STATE_HOLD)

#define KEYPAD_C_BASE           (KEYPAD_B_BASE << 1)
#define KEYPAD_C_PRESS          (KEYPAD_C_BASE + KEYPAD_STATE_PRESS)
#define KEYPAD_C_RELEASE        (KEYPAD_C_BASE + KEYPAD_STATE_RELEASE)
#define KEYPAD_C_HOLD           (KEYPAD_C_BASE + KEYPAD_STATE_HOLD)

void KEYPAD_Init(void);

uint8_t KEYPAD_Hit(void);
char KEYPAD_Read(void);

uint32_t KEYPAD_KeyEvent(void);

#endif /* __KEYPAD_H__ */

