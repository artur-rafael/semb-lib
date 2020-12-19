#ifndef __LCD_H__
#define __LCD_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>

#include "utils/ustdlib.h"

#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

#include "wait.h"

#define LCD_PORT                        GPIO_PORTA_BASE
#define LCD_ENABLE_PIN                  GPIO_PIN_2
#define LCD_RS_PIN                      GPIO_PIN_3
#define LCD_DB4_PIN                     GPIO_PIN_4
#define LCD_DB5_PIN                     GPIO_PIN_5
#define LCD_DB6_PIN                     GPIO_PIN_6
#define LCD_DB7_PIN                     GPIO_PIN_7
#define LCD_DB_PINS                     (LCD_DB7_PIN | LCD_DB6_PIN | LCD_DB5_PIN | LCD_DB4_PIN)

#define ENABLE_SHIFT                    2
#define RS_SHIFT                        3
#define DB_SHIFT                        4


#define LCD_FUNCTION_SET_BASE           0x20
#define LCD_4DL                         0
#define LCD_N_LINES                     0
#define LCD_FONT                        0
#define LCD_FUNCTION_SET                (LCD_FUNCTION_SET_BASE | LCD_4DL | LCD_N_LINES | LCD_FONT)

#define LCD_ENTRY_MODE_SET_BASE         0x04
#define LCD_INC_DEC                     0x02
#define LCD_DISPLAY_SHIFT               0
#define LCD_ENTRY_MODE_SET              (LCD_ENTRY_MODE_SET_BASE | LCD_INC_DEC | LCD_DISPLAY_SHIFT)

#define LCD_DISPLAY_CURSOR_BLINK_BASE   0b1000
#define LCD_DISPLAY_ON                  0b100
#define LCD_DISPLAY_OFF                 0b1011
#define LCD_CURSOR_ON                   0b10
#define LCD_CURSOR_OFF                  0b1101
#define LCD_BLINK_ON                    0b1
#define LCD_BLINK_OFF                   0b1110

#define LCD_CLEAR_DISPLAY               0x01
#define LCD_RETURN_HOME                 0x02
#define LCD_SET_DDRAM_ADDR_BASE         0x80

#define LCD_DISPLAY_SIZE                20

typedef enum {
    MODE_4,
    MODE_8
} LCD_ModeSize;

typedef enum {
    INSTRUCTION = 0,
    DATA = 1
} LCD_Type;

typedef enum {
    DISPLAY_ON = LCD_DISPLAY_ON,
    DISPLAY_OFF = LCD_DISPLAY_OFF
} LCD_DisplayState;

typedef enum {
    CURSOR_ON = LCD_CURSOR_ON,
    CURSOR_OFF = LCD_CURSOR_OFF
} LCD_CursorState;

typedef enum {
    BLINK_ON = LCD_BLINK_ON,
    BLINK_OFF = LCD_BLINK_OFF
} LCD_BlinkState;

void LCD_Init(void);

void LCD_WriteChar(char ch);
void LCD_WriteString(char * str);
void LCD_Printf(char * fmt, ...);
void LCD_CenteredPrintf(char * fmt, ...);

void LCD_Clear(void);
void LCD_Home(void);

void LCD_Display(LCD_DisplayState display);
void LCD_Cursor(LCD_CursorState cursor);
void LCD_Blink(LCD_BlinkState blink);

void LCD_SetCursor(uint8_t ddram);

#endif /* __LCD_H__ */
