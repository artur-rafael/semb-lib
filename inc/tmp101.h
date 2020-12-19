#ifndef __TMP101_H__
#define __TMP101_H__

#include <stdint.h>
#include <stdbool.h>

#include "i2c.h"

#define TMP101_ADDRESS                  0x48

#define TMP101_CONFIG_REGISTER_ADDRESS  0x01
#define TMP101_CONFIG_REGISTER_SIZE     2
#define TMP101_CONFIG_SD                0
#define TMP101_CONFIG_TM                (TMP101_CONFIG_SD + 1)
#define TMP101_CONFIG_POL               (TMP101_CONFIG_TM + 1)
#define TMP101_CONFIG_FAULT             (TMP101_CONFIG_POL + 2)
#define TMP101_CONFIG_RES               (TMP101_CONFIG_FAULT + 2)
#define TMP101_CONFIG_OS                (TMP101_CONFIG_RES + 1)

#define TMP101_TEMP_REGISTER_ADDRESS    0x00
#define TMP101_TEMP_REGISTER_SIZE       2
#define TMP101_TEMP_LSB                 1
#define TMP101_TEMP_MSB                 0

typedef enum {
    SHUTDOWN_MODE_OFF,
    SHUTDOWN_MODE_ON
} TMP101_SD;

typedef enum {
    COMPARATOR_MODE,
    INTERRUPT_MODE
} TMP101_TM;

typedef enum {
    ALERT_ACTIVE_LOW,
    ALERT_ACTIVE_HIGH
} TMP101_POL;

void TMP101_Init(void);
float TMP101_GetTemperature(void);

#endif /* __TMP101_H__ */
