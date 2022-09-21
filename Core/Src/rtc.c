#include "rtc.h"

extern I2C_HandleTypeDef hi2c2;

char temperatureDs[7];
char yearDs[5];
uint8_t Buffer_RTC[18];
char s_uint_to_char[3];
const uint8_t array_Date_Automatic_Time_Translation[19] = {26, 29, 1, 28, 31, 27, 30, 1, 28, 31, 27,
                                                      30, 26, 29, 1, 27, 30, 26, 29};
_Bool perevedeno = 0;
uint8_t sec = 0;
uint8_t min = 0;
uint8_t hour = 0;
uint8_t day = 0;
uint8_t date = 0;
uint8_t mounth = 0;
uint8_t year = 0;
uint8_t temperat1 = 0;
uint8_t temperat_z = 0;
uint8_t size_string_day = 0;
uint8_t size_string_mounth = 0;

void I2C_WriteBuffer(I2C_HandleTypeDef struct_time, uint16_t DEV_ADDR, uint8_t size_buf)
{
	while(HAL_I2C_Master_Transmit(&struct_time, (uint16_t) DEV_ADDR, (uint8_t*) &Buffer_RTC, (uint16_t) size_buf, (uint32_t)1000) != HAL_OK)
		if(HAL_I2C_GetError(&struct_time) != HAL_I2C_ERROR_AF) {}
}

void I2C_ReadBuffer(I2C_HandleTypeDef struct_time, uint16_t DEV_ADDR, uint8_t size_buf)
{
	while(HAL_I2C_Master_Receive(&struct_time, (uint16_t) DEV_ADDR, (uint8_t*) &Buffer_RTC, (uint16_t) size_buf, (uint32_t)1000) != HAL_OK)
		if(HAL_I2C_GetError(&struct_time) != HAL_I2C_ERROR_AF) {}
}

uint8_t RTC_ConvertFromDec(uint8_t d)
{
	uint8_t ch = ((d >> 4) * 10 + (0x0F & d));
	return ch;
}

uint8_t RTC_ConvertFromBinDec(uint8_t d)
{
	uint8_t ch = ((d / 10) << 4) | (d % 10);
	return ch;
}

void temperatureDs3231(void)
{
	if(temperat_z == 0) temperatureDs[0] = '+';
	else temperatureDs[0] = '-';
	temperatureDs[1] = (char) ((temperat1 / 10) % 10) + 0x30;
	temperatureDs[2] = (char) (temperat1 % 10) + 0x30;
	temperatureDs[3] = '@';
	temperatureDs[4] = 208;
	temperatureDs[5] = 161;
	temperatureDs[6] = '\0';
}

void convertUintToChar(uint8_t x)
{
  s_uint_to_char[0] = (char) ((x / 10) % 10) + 0x30;
  s_uint_to_char[1] = (char) (x % 10) + 0x30;
  s_uint_to_char[2] = '\0';
}

void setTime(void)
{
  Buffer_RTC[0] = 0x00;
  Buffer_RTC[1] = RTC_ConvertFromBinDec(sec);//секунды(0-59)
  Buffer_RTC[2] = RTC_ConvertFromBinDec(min);//минуты(0-59)
  Buffer_RTC[3] = RTC_ConvertFromBinDec(hour);//часы(1-12+AM/PM или 00-23)
  Buffer_RTC[4] = RTC_ConvertFromBinDec(day);//день недели(1 вос - 7 суб)
  Buffer_RTC[5] = RTC_ConvertFromBinDec(date);//дата(01-31)
  Buffer_RTC[6] = RTC_ConvertFromBinDec(mounth);//месяц(01-12)
  Buffer_RTC[7] = RTC_ConvertFromBinDec(year);//год(00-99)
  I2C_WriteBuffer(hi2c2, (uint16_t) 0xD0, 1);
  while(HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY) {}
  I2C_WriteBuffer(hi2c2, (uint16_t) 0xD0, 8);
}

void getRTC(void)
{
  Buffer_RTC[0] = 0x00;
	I2C_WriteBuffer(hi2c2, (uint16_t)0xD0, (uint8_t)1);
	while(HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY) {}
	I2C_ReadBuffer(hi2c2, (uint16_t)0xD0, (uint8_t)18);
	sec = RTC_ConvertFromDec(Buffer_RTC[0]);
	min = RTC_ConvertFromDec(Buffer_RTC[1]);
	hour = RTC_ConvertFromDec(Buffer_RTC[2]);
	day = RTC_ConvertFromDec(Buffer_RTC[3]);
	date = RTC_ConvertFromDec(Buffer_RTC[4]);
	mounth = RTC_ConvertFromDec(Buffer_RTC[5]);
	year = RTC_ConvertFromDec(Buffer_RTC[6]);
	temperat1 = Buffer_RTC[17] & 0b01111111;
	temperat_z = Buffer_RTC[17] & 0b10000000;
}

char *getTimeS(void)
{
	convertUintToChar(sec);
	char *s1 = s_uint_to_char;
	return s1;
}

char *getTimeMi(void)
{
	convertUintToChar(min);
	char *s1 = s_uint_to_char;
	return s1;
}

char *getTimeH(void)
{
	convertUintToChar(hour);
	char *s1 = s_uint_to_char;
  return s1;
}

char *getTimeDW(void)
{
	convertUintToChar(day);
	char *s1 = s_uint_to_char;
  return s1;
}

char *getTimeDayW(void)
{
  char *ds;
    
  switch(day){
    case 1:
      ds = "воскресенье";
      size_string_day = 11;
      break;
    case 2:
      ds = "понедельник";
      size_string_day = 11;
      break;
    case 3:
      ds = "вторник";
      size_string_day = 7;
      break;
    case 4:
      ds = "среда";
      size_string_day = 5;
      break;
    case 5:
      ds = "четверг";
      size_string_day = 7;
      break;
    case 6:
      ds = "пятница";
      size_string_day = 7;
      break;
    case 7:
      ds = "суббота";
      size_string_day = 7;
      break;
  }

  return ds;
}

char *getTimeDM(void)
{
	convertUintToChar(date);
	char *s1 = s_uint_to_char;
  return s1;
}

char *getTimeMo(void)
{
	convertUintToChar(mounth);
	char *s1 = s_uint_to_char;
  return s1;
}

char *getTimeMounth(void)
{
  char *m;
    
  switch(mounth){
    case 1:
      m = "январь";
      size_string_mounth = 6;
      break;
    case 2:
      m = "февраль";
      size_string_mounth = 7;
      break;
    case 3:
      m = "март";
      size_string_mounth = 4;
      break;
    case 4:
      m = "апрель";
      size_string_mounth = 6;
      break;
    case 5:
      m = "май";
      size_string_mounth = 3;
      break;
    case 6:
      m = "июнь";
      size_string_mounth = 4;
      break;
    case 7:
      m = "июль";
      size_string_mounth = 4;
      break;
    case 8:
      m = "август";
      size_string_mounth = 6;
      break;
    case 9:
      m = "сентябрь";
      size_string_mounth = 8;
      break;
    case 10:
      m = "октябрь";
      size_string_mounth = 7;
      break;
    case 11:
      m = "ноябрь";
      size_string_mounth = 6;
      break;
    case 12:
      m = "декабрь";
      size_string_mounth = 7;
      break;
  }
    
  return m;
}

char *getTimeYe(void)
{
  convertUintToChar(year);
	char *s1 = s_uint_to_char;
  return s1;
}

void getTimeY(void)
{
	yearDs[0] = '2';
	yearDs[1] = '0';
	yearDs[2] = (char) ((year / 10) % 10) + 0x30;
	yearDs[3] = (char) (year % 10) + 0x30;
	yearDs[4] = '\0';
}

uint8_t getSizeStringDay(void)
{
  return size_string_day;
}

uint8_t getSizeStringMounth(void)
{
  return size_string_mounth;
}


void automaticTimeTranslation(void)
{
  if(mounth == 10 && year == 20) translationMounthOctober(0);
  else if(mounth == 3 && year == 21) translationMounthMarch(1);
  else if(mounth == 11 && year == 21) translationMounthOctober(2);
  else if(mounth == 3 && year == 22) translationMounthMarch(3);
  else if(mounth == 10 && year == 22) translationMounthOctober(4);
  else if(mounth == 3 && year == 23) translationMounthMarch(5);
  else if(mounth == 10 && year == 23) translationMounthOctober(6);
  else if(mounth == 4 && year == 24) translationMounthMarch(7);
  else if(mounth == 10 && year == 24) translationMounthOctober(8);
  else if(mounth == 3 && year == 25) translationMounthMarch(9);
  else if(mounth == 10 && year == 25) translationMounthOctober(10);
  else if(mounth == 3 && year == 26) translationMounthMarch(11);
  else if(mounth == 10 && year == 26) translationMounthOctober(12);
  else if(mounth == 3 && year == 27) translationMounthMarch(13);
  else if(mounth == 11 && year == 27) translationMounthOctober(14);
  else if(mounth == 3 && year == 28) translationMounthMarch(15);
  else if(mounth == 10 && year == 28) translationMounthOctober(16);
  else if(mounth == 3 && year == 29) translationMounthMarch(17);
  else if(mounth == 10 && year == 29) translationMounthOctober(18);
}

void translationMounthMarch(uint8_t y)
{
  if(date == array_Date_Automatic_Time_Translation[y]){
    if(hour == 10 && !perevedeno){
      hour = 11;
      setTime();
      perevedeno = 1;
    }
    else if(hour > 11) perevedeno = 0;
  }
}

void translationMounthOctober(uint8_t y)
{
  if(date == array_Date_Automatic_Time_Translation[y]){
    if(hour == 11 && !perevedeno){
      hour = 10;
      setTime();
      perevedeno = 1;
    }
    else if(hour > 11) perevedeno = 0;
  } 
}
