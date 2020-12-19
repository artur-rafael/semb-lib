#include "i2c.h"

#define DEBUG_MODE                  0

#if DEBUG_MODE
#include "utils/uartstdio.h"
#define DEBUG_TIVA_SLAVE_ADDRESS    0x3C
#define DEBUG_STARTING_BYTE_RECEIVE 'A'
#define DEBUG_PRINT_BYTE(byte)      UARTprintf("[%s, %d] %c\n", __FUNCTION__, __LINE__, byte);
#endif

/***************************** Global Variables *****************************/

static I2C_GPIO_Config _g[I2C_MODULES] = {
                                          {SYSCTL_PERIPH_GPIOB, GPIO_PB2_I2C0SCL, GPIO_PB3_I2C0SDA, GPIO_PORTB_BASE, GPIO_PIN_2, GPIO_PIN_3},
                                          {SYSCTL_PERIPH_GPIOA, GPIO_PA6_I2C1SCL, GPIO_PA7_I2C1SDA, GPIO_PORTA_BASE, GPIO_PIN_6, GPIO_PIN_7},
                                          {SYSCTL_PERIPH_GPIOE, GPIO_PE4_I2C2SCL, GPIO_PE5_I2C2SDA, GPIO_PORTE_BASE, GPIO_PIN_4, GPIO_PIN_5},
                                          {SYSCTL_PERIPH_GPIOD, GPIO_PD0_I2C3SCL, GPIO_PD1_I2C3SDA, GPIO_PORTD_BASE, GPIO_PIN_0, GPIO_PIN_1},
                                         };
static I2C_Config _i[I2C_MODULES] = {
                                     {SYSCTL_PERIPH_I2C0, I2C0_BASE},
                                     {SYSCTL_PERIPH_I2C1, I2C1_BASE},
                                     {SYSCTL_PERIPH_I2C2, I2C2_BASE},
                                     {SYSCTL_PERIPH_I2C3, I2C3_BASE},
                                    };
static uint32_t _i2cBase;
static bool _repeatedStart;

static uint8_t _slaveAddress;
static uint8_t * _tx;
static size_t _txSize;
static uint8_t * _rx;
static size_t _rxSize;

#if DEBUG_MODE
static uint8_t _data;
#endif

/*************************** Functions Signatures ***************************/

static void I2C_Send(void);
static void I2C_Receive(void);

/****************************************************************************/
/********************************* Functions ********************************/
/****************************************************************************/

void I2C_Init(I2C_Module module) {
    I2C_GPIO_Config * g = &_g[module];
    I2C_Config * i = &_i[module];

    SysCtlPeripheralEnable(i->SYSCTL_PERIPH_I2Cx);
    while(!SysCtlPeripheralReady(i->SYSCTL_PERIPH_I2Cx));
    SysCtlPeripheralReset(i->SYSCTL_PERIPH_I2Cx);
    while(!SysCtlPeripheralReady(i->SYSCTL_PERIPH_I2Cx));

    SysCtlPeripheralEnable(g->SYSTCL_PERIPH_GPIOx);
    while(!SysCtlPeripheralReady(g->SYSTCL_PERIPH_GPIOx));
    GPIOPinConfigure(g->GPIO_Px_I2CxSCL);
    GPIOPinConfigure(g->GPIO_Px_I2CxSDA);
    GPIOPinTypeI2CSCL(g->GPIO_PORTx_BASE, g->GPIO_PIN_x_SCL);
    GPIOPinTypeI2C(g->GPIO_PORTx_BASE, g->GPIO_PIN_x_SDA);

    I2CMasterInitExpClk(i->I2Cx_BASE, SysCtlClockGet(), false);

#if DEBUG_MODE
    I2CLoopbackEnable(i->I2Cx_BASE);
    I2CSlaveEnable(i->I2Cx_BASE);
    I2CSlaveInit(i->I2Cx_BASE, DEBUG_TIVA_SLAVE_ADDRESS);
#endif
} /* I2C_Init() */

void I2C_Transfer(I2C_Module module, uint8_t slaveAddress, uint8_t * tx, size_t txSize, uint8_t * rx, size_t rxSize) {
    _i2cBase = _i[module].I2Cx_BASE;
    _repeatedStart = (rx != NULL) ? true : false;

    _slaveAddress = slaveAddress;
    _tx = tx;
    _txSize = txSize;
    _rx = rx;
    _rxSize = rxSize;

    I2C_Send();
    if(_rx)
        I2C_Receive();
} /* I2C_Transfer() */

/****************************************************************************/
/***************************** Static Functions *****************************/
/****************************************************************************/

static void I2C_Send(void) {
    size_t txIndex = 0;

    I2CMasterSlaveAddrSet(_i2cBase, _slaveAddress, I2C_MASTER_WRITE);

    while(txIndex < _txSize) {
        I2CMasterDataPut(_i2cBase, _tx[txIndex]);

        if(1 && _txSize == 1) { /* Send one byte, only if there ins't a read to do */
            I2CMasterControl(_i2cBase, I2C_MASTER_CMD_SINGLE_SEND);
        } else if(txIndex == 0) { /* Send first byte, if there is a read we need to send a Burst instead of a Single */
            I2CMasterControl(_i2cBase, I2C_MASTER_CMD_BURST_SEND_START);
        } else if(!_repeatedStart && txIndex == _txSize - 1) { /* Send last byte, only if there ins't a read to do */
            I2CMasterControl(_i2cBase, I2C_MASTER_CMD_BURST_SEND_FINISH);
        } else { /* Send all other bytes */
            I2CMasterControl(_i2cBase, I2C_MASTER_CMD_BURST_SEND_CONT);
        }
#if DEBUG_MODE
        while(!(I2CSlaveStatus(_i2cBase) & I2C_SLAVE_ACT_RREQ));
        _data = I2CSlaveDataGet(_i2cBase);
        DEBUG_PRINT_BYTE(_data)
#endif

        while(I2CMasterBusy(_i2cBase));
        //TODO: Check for errors
        ++txIndex;
    }
} /* I2C_Send() */

static void I2C_Receive(void) {
    size_t rxIndex = 0;
#if DEBUG_MODE
    uint8_t debugByte = DEBUG_STARTING_BYTE_RECEIVE;
#endif

    I2CMasterSlaveAddrSet(_i2cBase, _slaveAddress, I2C_MASTER_READ);

    while(rxIndex < _rxSize) {
        if(_rxSize == 1) { /* Receive one byte */
            I2CMasterControl(_i2cBase, I2C_MASTER_CMD_SINGLE_RECEIVE);
        } else if(rxIndex == 0) { /* Receive first byte */
            I2CMasterControl(_i2cBase, I2C_MASTER_CMD_BURST_RECEIVE_START);
        } else if(rxIndex == _rxSize - 1) { /* Receive last byte */
            I2CMasterControl(_i2cBase, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
        } else { /* Receive all other bytes */
            I2CMasterControl(_i2cBase, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
        }
#if DEBUG_MODE
        while(!(I2CSlaveStatus(_i2cBase) & I2C_SLAVE_ACT_TREQ));
        I2CSlaveDataPut(_i2cBase, debugByte++);
#endif
        while(I2CMasterBusy(_i2cBase));

        //TODO: Check for errors

        _rx[rxIndex] = I2CMasterDataGet(_i2cBase);

#if DEBUG_MODE
        DEBUG_PRINT_BYTE(_rx[rxIndex]);
#endif
        ++rxIndex;
    }
} /* I2C_Receive() */
