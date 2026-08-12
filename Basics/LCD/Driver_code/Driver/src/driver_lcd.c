/*
 * driver_lcd.c
 *
 *  Created on: Jul 28, 2026
 *      Author: SRSL
 */


#include "driver_lcd.h"
#include "main.h"
#include "bsp_lcd.h"




/*=========================================================
 * Private Function Prototypes Start
 *========================================================*/

static void LCD_SendNibble(uint8_t nibble);

static void LCD_SendByte(uint8_t byte,
                         uint8_t rs);

static void LCD_SendCommand(uint8_t command);

static void LCD_SendData(uint8_t data);

/*=========================================================
 * Private Function Prototypes End
 *========================================================*/

static void LCD_SendNibble(uint8_t nibble)
{
    BSP_LCD_WriteNibble(nibble);

    BSP_LCD_PulseEnable();
}


/******************************************************************************
 * @brief  Sends one byte to the LCD in 4-bit mode.
 *
 * @param  byte 8-bit command or data.
 * @param  rs   0 = Command
 *              1 = Data
 ******************************************************************************/
static void LCD_SendByte(uint8_t byte, uint8_t rs)
{
    /* Select Command/Data Register */
    BSP_LCD_SetRS(rs);

    /* Send upper nibble */
    LCD_SendNibble((byte >> 4) & 0x0F);

    /* Send lower nibble */
    LCD_SendNibble(byte & 0x0F);
}

/******************************************************************************
 * @brief Sends a command to the LCD.
 *
 * @param command LCD command byte.
 ******************************************************************************/
static void LCD_SendCommand(uint8_t command)
{
    LCD_SendByte(command, 0U);
}

/******************************************************************************
 * @brief Sends one data byte (character) to the LCD.
 *
 * @param data ASCII character.
 ******************************************************************************/
static void LCD_SendData(uint8_t data)
{
    LCD_SendByte(data, 1U);
}


/*******************************************************************************
* LCD Initilization code
*******************************************************************************/

void LCD_Init(void)
{
    /* Wait for LCD power stabilization */
    HAL_Delay(50);

    /* Force LCD into 8-bit mode */
    LCD_SendNibble(0x03);
    HAL_Delay(5);

    LCD_SendNibble(0x03);
    BSP_LCD_DelayUs(150);

    LCD_SendNibble(0x03);
    BSP_LCD_DelayUs(150);

    /* Switch to 4-bit mode */
    LCD_SendNibble(0x02);
    BSP_LCD_DelayUs(150);

    /* Configure interface */
    LCD_SendCommand(LCD_CMD_FUNCTION_SET);

    /* Display OFF */
    LCD_SendCommand(LCD_CMD_DISPLAY_OFF);

    /* Clear display */
    LCD_SendCommand(LCD_CMD_CLEAR_DISPLAY);
    HAL_Delay(2);

    /* Entry mode */
    LCD_SendCommand(LCD_CMD_ENTRY_MODE_INC);

    /* Display ON */
    LCD_SendCommand(LCD_CMD_DISPLAY_ON);
}

/******************************************************************************
 * @brief Clears the LCD display and moves cursor to home position.
 ******************************************************************************/
void LCD_Clear(void)
{
    LCD_SendCommand(LCD_CMD_CLEAR_DISPLAY);

    /* Clear Display requires approximately 1.52 ms */
    HAL_Delay(2);
}

/******************************************************************************
 * @brief Moves cursor to home position.
 ******************************************************************************/
void LCD_Home(void)
{
    LCD_SendCommand(LCD_CMD_RETURN_HOME);

    HAL_Delay(2);
}


/******************************************************************************
 * @brief Turns ON the LCD display.
 ******************************************************************************/
void LCD_DisplayOn(void)
{
    LCD_SendCommand(LCD_CMD_DISPLAY_ON);
}

/******************************************************************************
 * @brief Turns OFF the LCD display.
 ******************************************************************************/
void LCD_DisplayOff(void)
{
    LCD_SendCommand(LCD_CMD_DISPLAY_OFF);
}


/******************************************************************************
 * @brief Writes a single character to the LCD.
 *
 * @param ch ASCII character to display.
 ******************************************************************************/
void LCD_WriteChar(char ch)
{
    LCD_SendData((uint8_t)ch);
}

/******************************************************************************
 * @brief Writes a NULL terminated string to the LCD.
 *
 * @param str Pointer to string.
 ******************************************************************************/
void LCD_WriteString(const char *str)
{
    if (str == NULL)
    {
        return;
    }

    while (*str != '\0')
    {
        LCD_WriteChar(*str);

        str++;
    }
}

/******************************************************************************
 * @brief Sets the LCD cursor position.
 *
 * @param row Row number (0-3)
 * @param col Column number
 ******************************************************************************/

static const uint8_t LCD_RowAddress[] =
{
    LCD_ROW_0_ADDRESS,
    LCD_ROW_1_ADDRESS,
    LCD_ROW_2_ADDRESS,
    LCD_ROW_3_ADDRESS
};

void LCD_SetCursor(uint8_t row, uint8_t col)
{
    uint8_t address;

    if (row >= LCD_ROWS)
    {
        return;
    }

    if (col >= LCD_COLUMNS)
    {
        return;
    }

    address = LCD_RowAddress[row] + col;

    LCD_SendCommand(LCD_CMD_SET_DDRAM_ADDR | address);
}
