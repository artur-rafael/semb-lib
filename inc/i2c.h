#ifndef __I2C_H__
#define __I2C_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/i2c.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"

#define I2C_DEBUG_TIVA_ADDRESS  0x3C

#define I2C_MASTER_WRITE        false
#define I2C_MASTER_READ         true

#define I2C_MODULES             4
#define I2C_TYPES               4

typedef struct {
    uint32_t SYSTCL_PERIPH_GPIOx;
    uint32_t GPIO_Px_I2CxSCL;
    uint32_t GPIO_Px_I2CxSDA;
    uint32_t GPIO_PORTx_BASE;
    uint8_t GPIO_PIN_x_SCL;
    uint8_t GPIO_PIN_x_SDA;
} I2C_GPIO_Config;

typedef struct {
    uint32_t SYSCTL_PERIPH_I2Cx;
    uint32_t I2Cx_BASE;
} I2C_Config;

typedef enum {
    I2C0,
    I2C1,
    I2C2,
    I2C3
} I2C_Module;

void I2C_Init(I2C_Module module);

void I2C_Transfer(I2C_Module module, uint8_t slaveAddress, uint8_t * tx, size_t txSize, uint8_t * rx, size_t rxSize);

#endif /* __I2C_H__ */
