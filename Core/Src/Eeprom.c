#include "Eeprom.h"
/*
int at24_HAL_WriteBytes(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint8_t *pData, uint16_t TxBufferSize)
{

	if(MemAddress + TxBufferSize > 16)
	{
		//Write to 16bytes
		while(HAL_I2C_Mem_Write(hi2c, (uint16_t)DevAddress, (uint16_t)MemAddress, I2C_MEMADD_SIZE_8BIT, pData, (uint16_t)16 - MemAddress, 1000)!= HAL_OK);
		//write remaining bytes
		*pData = *pData + (16 - MemAddress);
		while(HAL_I2C_Mem_Write(hi2c, (uint16_t)DevAddress, (uint16_t)16, I2C_MEMADD_SIZE_8BIT, pData, (uint16_t)((MemAddress+TxBufferSize) - 16), 1000) != HAL_OK);

	}
	else
	{
			while((TxBufferSize-16) > 0)
			{
				//if your data is more than 16 bytes,you are here
				 while(HAL_I2C_Mem_Write(&hi2c, (uint16_t)DevAddress, (uint16_t)MemAddress, I2C_MEMADD_SIZE_8BIT, pData, (uint16_t)16, 1000) != HAL_OK);
				 TxBufferSize -= 16;
				 pData += 16;
				 MemAddress += 16;
			}
			//remaining data
			while(HAL_I2C_Mem_Write(hi2c, (uint16_t)DevAddress, (uint16_t)MemAddress, I2C_MEMADD_SIZE_8BIT, pData, (uint16_t)TxBufferSize, 1000) != HAL_OK);
	}
	return 1;
}


int at24_HAL_ReadBytes(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint8_t *pData, uint16_t RxBufferSize)
{
	int TimeOut;


			while((RxBufferSize - 16) > 0)
			{
				//if your data is more than 16 bytes,you are here
				TimeOut = 0;
				 while(HAL_I2C_Mem_Read(hi2c, (uint16_t)DevAddress, (uint16_t)MemAddress, I2C_MEMADD_SIZE_8BIT, pData,(uint16_t)16, 1000) != HAL_OK && TimeOut < 10)
				 {
						TimeOut++;
				 }

				 RxBufferSize -= 16;
				 pData += 16;
				 MemAddress += 16;
			}
//			//remaining data
			TimeOut = 0;
			while(HAL_I2C_Mem_Read(hi2c, (uint16_t)DevAddress, (uint16_t)MemAddress, I2C_MEMADD_SIZE_8BIT, pData, (uint16_t)RxBufferSize, 1000) != HAL_OK && TimeOut < 10)
			{
				TimeOut++;
			}

	return 1;
}
*/

