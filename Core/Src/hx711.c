/*
 * hx711.c
 *
 *  Created on: Feb 16, 2021
 *      Author: Tấn Sơn
 */

#include "hx711.h"
#include "dwt_delay.h"
#include "Config.h"

unsigned long HX711_getValue(void)
{
    uint32_t data = 0;
    HAL_GPIO_WritePin(HX711data_Port, HX711data_Pin, 0);
    HAL_GPIO_WritePin(HX711clk_Port, HX711clk_Pin, 0);
    DWT_Delay_us(1);
    while (HAL_GPIO_ReadPin(HX711data_Port, HX711data_Pin) == 1);
    for (int8_t i = 0; i < 25; i++)
    {
        HAL_GPIO_WritePin(HX711clk_Port, HX711clk_Pin, 1);
        DWT_Delay_us(1);
        data = data << 1;

        if (HAL_GPIO_ReadPin(HX711data_Port, HX711data_Pin) == 1)
        {
            data ++;
        }
    }
    HAL_GPIO_WritePin(HX711clk_Port, HX711clk_Pin, 1);
    DWT_Delay_us(1);
    data = data ^ 0x800000;
    HAL_GPIO_WritePin(HX711clk_Port, HX711clk_Pin, 0);
    DWT_Delay_us(1);
    return (data);
}
