#ifndef INC_RTC_H_
#define INC_RTC_H_

#include "main.h"
#include "stm32f1xx_hal.h"

void I2C_WriteBuffer(I2C_HandleTypeDef struct_time, uint16_t DEV_ADDR, uint8_t size_buf);
void I2C_ReadBuffer(I2C_HandleTypeDef struct_time, uint16_t DEV_ADDR, uint8_t size_buf);
uint8_t RTC_ConvertFromDec(uint8_t d);
uint8_t RTC_ConvertFromBinDec(uint8_t d);
void temperatureDs3231(void);
void convertUintToChar(uint8_t x);
void setTime(void);
void getRTC(void);
char *getTimeS(void);
char *getTimeMi(void);
char *getTimeH(void);
char *getTimeDW(void);
char *getTimeDayW(void);
char *getTimeDM(void);
char *getTimeMo(void);
char *getTimeMounth(void);
char *getTimeYe(void);
void getTimeY(void);
uint8_t getSizeStringDay(void);
uint8_t getSizeStringMounth(void);
void automaticTimeTranslation(void);
void translationMounthMarch(uint8_t y);
void translationMounthOctober(uint8_t y);

#endif
