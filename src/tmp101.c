#include "tmp101.h"

/***************************** Global Variables *****************************/

/*************************** Functions Signatures ***************************/

static void TMP101_SetConfiguration(TMP101_SD sd, TMP101_TM tm, TMP101_POL pol, uint8_t fault, uint8_t res);

/****************************************************************************/
/********************************* Functions ********************************/
/****************************************************************************/

void TMP101_Init(void) {
    TMP101_SetConfiguration(SHUTDOWN_MODE_OFF, COMPARATOR_MODE, ALERT_ACTIVE_LOW, 0x00, 0x00);
} /* TMP101_Init() */

float TMP101_GetTemperature(void) {
    uint8_t reg = TMP101_TEMP_REGISTER_ADDRESS;
    uint8_t temp[TMP101_TEMP_REGISTER_SIZE] = {0};

    I2C_Transfer(I2C2, TMP101_ADDRESS, &reg, 1, temp, TMP101_TEMP_REGISTER_SIZE);

    return ((float) (((int16_t) temp[TMP101_TEMP_MSB] << 8) | temp[TMP101_TEMP_LSB]) / 256.0);
} /* TMP101_GetTemperature() */

/****************************************************************************/
/***************************** Static Functions *****************************/
/****************************************************************************/

static void TMP101_SetConfiguration(TMP101_SD sd, TMP101_TM tm, TMP101_POL pol, uint8_t fault, uint8_t res) {
    uint8_t config = sd << TMP101_CONFIG_SD |
                     tm << TMP101_CONFIG_TM |
                     pol << TMP101_CONFIG_POL |
                     (fault & 0x03) << TMP101_CONFIG_FAULT |
                     (res & 0x03) << TMP101_CONFIG_RES;

    uint8_t tx[TMP101_CONFIG_REGISTER_SIZE] = {TMP101_CONFIG_REGISTER_ADDRESS, config};

    I2C_Transfer(I2C2, TMP101_ADDRESS, tx, TMP101_CONFIG_REGISTER_SIZE, NULL, 0);
} /* TMP101_SetConfiguration() */
