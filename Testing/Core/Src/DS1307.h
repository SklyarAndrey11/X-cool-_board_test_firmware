/*
 * DS1307.h
 *
 *  Created on: Oct 24, 2023
 *      Author: Sklya
 */

#ifndef SRC_DS1307_H_
#define SRC_DS1307_H_
#include "main.h"
/*----------------------------------------------------------------------------*/
#define DS1307_I2C_ADDR 	0x68
#define DS1307_REG_SECOND 	0x00
#define DS1307_REG_MINUTE 	0x01
#define DS1307_REG_HOUR  	0x02
#define DS1307_REG_DOW    	0x03
#define DS1307_REG_DATE   	0x04
#define DS1307_REG_MONTH  	0x05
#define DS1307_REG_YEAR   	0x06
#define DS1307_REG_CONTROL 	0x07
#define DS1307_REG_UTC_HR	0x08
#define DS1307_REG_UTC_MIN	0x09
#define DS1307_REG_CENT    	0x10
#define DS1307_REG_RAM   	0x11
#define DS1307_TIMEOUT		1000
/*----------------------------------------------------------------------------*/
extern I2C_HandleTypeDef *_ds1307_ui2c;

void DS1307_SetDayOfWeek(uint8_t dow);
void DS1307_SetDay(uint8_t day);
void DS1307_SetMonth(uint8_t month);
void DS1307_SetYear(uint16_t year);

void DS1307_SetHour(uint8_t hour_24mode);
void DS1307_SetMinute(uint8_t minute);
void DS1307_SetSecond(uint8_t second);
void DS1307_SetTimeZone(int8_t hr, uint8_t min);

uint8_t DS1307_DecodeBCD(uint8_t bin);
uint8_t DS1307_EncodeBCD(uint8_t dec);

void DS1307_SetDate(uint8_t day, uint8_t month, uint16_t year);
void DS1307_SetTime(uint8_t hour, uint8_t min, uint8_t sec);

HAL_StatusTypeDef DS1307_GetDate(uint8_t* day, uint8_t* month, uint16_t* year);
HAL_StatusTypeDef DS1307_GetTime(uint8_t* hour, uint8_t* min, uint8_t* second);
#endif /* SRC_DS1307_H_ */
