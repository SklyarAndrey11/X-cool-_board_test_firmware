/*
 * BQ25731.c
 *
 *  Created on: Nov 13, 2023
 *      Author: Andrey
 */


#include "BQ25731.h"
#include "main.h"
#define BQ25731_I2C     hi2c1

#define BQ25731_ADDR    0x6B


HAL_StatusTypeDef bq25731_read_reg(uint8_t reg, uint8_t *data, uint8_t len)
{
	return  HAL_I2C_Mem_Read(&BQ25731_I2C, BQ25731_ADDR << 7, reg, 1 , data, len, 100);
}
HAL_StatusTypeDef bq25731_write_reg(uint8_t reg, uint8_t *data, uint8_t len)
{
	return HAL_I2C_Mem_Write(&BQ25731_I2C, BQ25731_ADDR << 7 | 0x01, reg, 1 , data, len, 100);
}





