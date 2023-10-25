/*
 * DS1307.c
 *
 *  Created on: Oct 24, 2023
 *      Author: Sklya
 */
#include "DS1307.h"
#include "main.h"
#ifdef __cplusplus
extern "C"{
#endif

I2C_HandleTypeDef *_ds1307_ui2c;

/**
 * @brief Sets the current day of week.
 * @param dayOfWeek Days since last Sunday, 0 to 6.
 */
void DS1307_SetDayOfWeek(uint8_t dayOfWeek) {
	DS1307_SetRegByte(DS1307_REG_DOW, DS1307_EncodeBCD(dayOfWeek));
}

/**
 * @brief Sets the current day of month.
 * @param date Day of month, 1 to 31.
 */
void DS1307_SetDay(uint8_t day) {
	DS1307_SetRegByte(DS1307_REG_DATE, DS1307_EncodeBCD(day));
}

/**
 * @brief Sets the current month.
 * @param month Month, 1 to 12.
 */
void DS1307_SetMonth(uint8_t month) {
	DS1307_SetRegByte(DS1307_REG_MONTH, DS1307_EncodeBCD(month));
}

/**
 * @brief Sets the current year.
 * @param year Year, 2000 to 2099.
 */
void DS1307_SetYear(uint16_t year) {
	DS1307_SetRegByte(DS1307_REG_CENT, year / 100);
	DS1307_SetRegByte(DS1307_REG_YEAR, DS1307_EncodeBCD(year % 100));
}

/**
 * @brief Sets the current hour, in 24h format.
 * @param hour_24mode Hour in 24h format, 0 to 23.
 */
void DS1307_SetHour(uint8_t hour_24mode) {
	DS1307_SetRegByte(DS1307_REG_HOUR, DS1307_EncodeBCD(hour_24mode & 0x3f));
}

/**
 * @brief Sets the current minute.
 * @param minute Minute, 0 to 59.
 */
void DS1307_SetMinute(uint8_t minute) {
	DS1307_SetRegByte(DS1307_REG_MINUTE, DS1307_EncodeBCD(minute));
}

/**
 * @brief Sets the current second.
 * @param second Second, 0 to 59.
 */
void DS1307_SetSecond(uint8_t second) {
	uint8_t ch = DS1307_GetClockHalt();
	DS1307_SetRegByte(DS1307_REG_SECOND, DS1307_EncodeBCD(second | ch));
}

/**
 * @brief Sets UTC offset.
 * @note  UTC offset is not updated automatically.
 * @param hr UTC hour offset, -12 to 12.
 * @param min UTC minute offset, 0 to 59.
 */
void DS1307_SetTimeZone(int8_t hr, uint8_t min) {
	DS1307_SetRegByte(DS1307_REG_UTC_HR, hr);
	DS1307_SetRegByte(DS1307_REG_UTC_MIN, min);
}
/**
 * @brief Sets day,month,year
 * @param day: Day of month
 * @param month: Month of year
 * @param year: 2000 to 2099.
 * @param min UTC minute offset, 0 to 59.
 */
void DS1307_SetDate(uint8_t day, uint8_t month, uint16_t year)
{
	DS1307_SetDay(day);
	DS1307_SetMonth(month);
	DS1307_SetYear(year);
}
/**
 * @brief Sets second, minute, hour
 * @param day: second 0-60
 * @param minute: minute 0-60
 * @param hour: hour 0-23.
 * @param min UTC minute offset, 0 to 59.
 */
void DS1307_SetTime(uint8_t hour, uint8_t min, uint8_t sec)
{
	DS1307_SetHour(hour);
	DS1307_SetMinute(min);
	DS1307_SetSecond(sec);
}

/**
 * @brief Decodes the raw binary value stored in registers to decimal format.
 * @param bin Binary-coded decimal value retrieved from register, 0 to 255.
 * @return Decoded decimal value.
 */
uint8_t DS1307_DecodeBCD(uint8_t bin) {
	return (((bin & 0xf0) >> 4) * 10) + (bin & 0x0f);
}

/**
 * @brief Encodes a decimal number to binaty-coded decimal for storage in registers.
 * @param dec Decimal number to encode.
 * @return Encoded binary-coded decimal value.
 */
uint8_t DS1307_EncodeBCD(uint8_t dec) {
	return (dec % 10 + ((dec / 10) << 4));
}

/**
 * @brief Get day,month,year faster
 * @param day: Day of month
 * @param month: Month of year
 * @param year: 2000 to 2099.
 */

HAL_StatusTypeDef DS1307_GetDate(uint8_t* day, uint8_t* month, uint16_t* year)
{
	HAL_StatusTypeDef status;
#define NUM_BYTE_READ         3
	static uint8_t temp[NUM_BYTE_READ];
	uint8_t reg = DS1307_REG_DATE;
	uint8_t cen;
	//Get 3 byte day,month,year continuously
	status = HAL_I2C_Master_Transmit(_ds1307_ui2c, (uint16_t)(DS1307_I2C_ADDR << 1),&reg , 1, DS1307_TIMEOUT);
	status = HAL_I2C_Master_Receive(_ds1307_ui2c, (uint16_t)(DS1307_I2C_ADDR << 1), temp, NUM_BYTE_READ, DS1307_TIMEOUT);
	if(status != HAL_OK) return status;
	//Get byte century
	reg = DS1307_REG_CENT;
	status = HAL_I2C_Master_Transmit(_ds1307_ui2c, (uint16_t)(DS1307_I2C_ADDR << 1), &reg, 1, DS1307_TIMEOUT);
	if(status != HAL_OK) return status;
	status = HAL_I2C_Master_Receive(_ds1307_ui2c, (uint16_t)(DS1307_I2C_ADDR << 1), &cen, 1, DS1307_TIMEOUT);
	if(status != HAL_OK) return status;

	//Convert
	*day = DS1307_DecodeBCD(temp[0]);//first byte
	*month = DS1307_DecodeBCD(temp[1]);
	*year = cen * 100 + DS1307_DecodeBCD(temp[1]);

	return HAL_OK;
}


/**
 * @brief Get hour, min, second
 * @param day: hour, min, second
 * return: HAL status
 */

HAL_StatusTypeDef DS1307_GetTime(uint8_t* hour, uint8_t* min, uint8_t* second)
{
	HAL_StatusTypeDef status;
#define NUM_BYTE_READ         3
	static uint8_t temp[NUM_BYTE_READ];
	uint8_t reg = DS1307_REG_SECOND;
	//Get 3 byte day,month,year continuously
	status = HAL_I2C_Master_Transmit(_ds1307_ui2c, DS1307_I2C_ADDR << 1, &reg, 1, DS1307_TIMEOUT);
	status = HAL_I2C_Master_Receive(_ds1307_ui2c, DS1307_I2C_ADDR << 1, temp, NUM_BYTE_READ, DS1307_TIMEOUT);
	if(status != HAL_OK) return status;


	//Convert
	*second = DS1307_DecodeBCD(temp[0]);//first byte
	*min = DS1307_DecodeBCD(temp[1]);
	*hour = DS1307_DecodeBCD(temp[1]);

	return HAL_OK;
}

#ifdef __cplusplus
}
#endif


