/*
 * bsp_lcd.c
 *
 *  Created on: Jul 28, 2026
 *      Author: SRSL
 */

/*
 This file contains the definations of functions declared in bsp_lcd.h
*/

#include "bsp_lcd.h"
#include"main.h"

void BSP_LCD_SetRS(uint8_t state)
{
	HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void BSP_LCD_WriteNibble(uint8_t nibble)
{
	HAL_GPIO_WritePin(LCD_D4_GPIO_Port, LCD_D4_Pin, (nibble & 0x01U) ? GPIO_PIN_SET : GPIO_PIN_RESET);

	HAL_GPIO_WritePin(LCD_D5_GPIO_Port, LCD_D5_Pin, (nibble & 0x02U) ? GPIO_PIN_SET : GPIO_PIN_RESET);

	HAL_GPIO_WritePin(LCD_D6_GPIO_Port, LCD_D6_Pin, (nibble & 0x04U) ? GPIO_PIN_SET : GPIO_PIN_RESET);

	HAL_GPIO_WritePin(LCD_D7_GPIO_Port, LCD_D7_Pin, (nibble & 0x08U) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void BSP_LCD_PulseEnable()
{
	HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, GPIO_PIN_SET);
	BSP_LCD_DelayUs(1);
	HAL_GPIO_WritePin(LCD_EN_GPIO_Port, LCD_EN_Pin, GPIO_PIN_RESET);
}

void BSP_LCD_DelayUs(uint8_t us)
{
	HAL_Delay(1);
}
