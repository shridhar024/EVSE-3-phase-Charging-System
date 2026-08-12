/*
 * lcd_driver.h
 *
 *  Created on: Jul 28, 2026
 *      Author: SRSL
 */

#ifndef INC_DRIVER_LCD_H_
#define INC_DRIVER_LCD_H_

#include <stdint.h>



/******************************************************************************
 * LCD Configuration
 ******************************************************************************/

#define LCD_ROWS        (4U)      // Change to 4U for 20x4, change to 4U for 16x4, for 16x2 use 2U
#define LCD_COLUMNS     (16U)     // Change to 20U for 20x4,change to 16 for 16x4, for 16x2 use 16U

#if (LCD_ROWS == 1U)

#define LCD_CMD_FUNCTION_SET LCD_CMD_FUNCTION_SET_4BIT_1LINE

#else

#define LCD_CMD_FUNCTION_SET LCD_CMD_FUNCTION_SET_4BIT_2LINE

#endif


/******************************************************************************
 * HD44780 LCD Command Definitions
 ******************************************************************************/

/* Basic Commands */
#define LCD_CMD_CLEAR_DISPLAY        (0x01U)
#define LCD_CMD_RETURN_HOME          (0x02U)

/* Entry Mode Set */
#define LCD_CMD_ENTRY_MODE_INC       (0x06U)
#define LCD_CMD_ENTRY_MODE_DEC       (0x04U)

/* Display Control */
#define LCD_CMD_DISPLAY_OFF          (0x08U)
#define LCD_CMD_DISPLAY_ON           (0x0CU)

#define LCD_CMD_CURSOR_ON            (0x0EU)
#define LCD_CMD_CURSOR_BLINK         (0x0FU)

/* Function Set */
#define LCD_CMD_FUNCTION_SET_4BIT_1LINE  (0x20U)
#define LCD_CMD_FUNCTION_SET_4BIT_2LINE  (0x28U)

#define LCD_CMD_FUNCTION_SET_8BIT_1LINE  (0x30U)
#define LCD_CMD_FUNCTION_SET_8BIT_2LINE  (0x38U)

/* DDRAM */
#define LCD_CMD_SET_DDRAM_ADDR       (0x80U)

/* CGRAM */
#define LCD_CMD_SET_CGRAM_ADDR       (0x40U)

#if (LCD_COLUMNS == 16U)

#define LCD_ROW_0_ADDRESS    0x00U
#define LCD_ROW_1_ADDRESS    0x40U
#define LCD_ROW_2_ADDRESS    0x10U
#define LCD_ROW_3_ADDRESS    0x50U

#elif (LCD_COLUMNS == 20U)

#define LCD_ROW_0_ADDRESS    0x00U
#define LCD_ROW_1_ADDRESS    0x40U
#define LCD_ROW_2_ADDRESS    0x14U
#define LCD_ROW_3_ADDRESS    0x54U

#else
#error "Unsupported LCD geometry"
#endif



/* Initialization */
void LCD_Init(void);

/* Basic Commands */
void LCD_Clear(void);
void LCD_Home(void);

/* Cursor */
void LCD_SetCursor(uint8_t row, uint8_t column);

/* Data */
void LCD_WriteChar(char ch);
void LCD_WriteString(const char *str);

/* Optional */
void LCD_DisplayOn(void);
void LCD_DisplayOff(void);

/* Private funcitons */
//static void LCD_SendNibble(uint8_t nibble);


#endif /* INC_DRIVER_LCD_H_ */
