#include "matrix_tablo_tpic.h"

extern SPI_HandleTypeDef hspi2;

uint8_t stroka = 0;
uint8_t num_shift_ticker[3] = {0, 0, 0};

uint8_t aTxBuffer[matrix_in_tablo] = {0};
uint8_t BufferTablo[8][matrix_in_tablo] = {0};
uint8_t BufferTabloTicker[8][153] = {0};
_Bool if_ticker = 0;
int show_seven_lines = 0;

uint8_t count_line_ticker = 0;
uint8_t count_line = 0;
uint8_t temp_line1 = 255;
uint8_t temp_line2 = 255;
uint8_t temp_line3 = 255;
_Bool temp_line = 1;


const uint8_t letters_and_numbers[51][8] = {
	{0x0E, 0x1E, 0x36, 0x66, 0x7E, 0x66, 0x66, 0x00},//0-А
	{0x7C, 0x60, 0x60, 0x7C, 0x66, 0x66, 0x7C, 0x00},//1-Б
	{0x7C, 0x66, 0x66, 0x7C, 0x66, 0x66, 0x7C, 0x00},//2-В
	{0x7E, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x00},//3-Г
	{0x1C, 0x3C, 0x2C, 0x2C, 0x2C, 0x7E, 0x66, 0x00},//4-Д
	{0x7E, 0x60, 0x60, 0x7C, 0x60, 0x60, 0x7E, 0x00},//5-Е
	{0x5A, 0x5A, 0x3C, 0x3C, 0x3C, 0x5A, 0x5A, 0x00},//6-Ж
	{0x3C, 0x66, 0x06, 0x1C, 0x06, 0x66, 0x3C, 0x00},//7-З
	{0x66, 0x66, 0x6E, 0x7E, 0x76, 0x66, 0x66, 0x00},//8-И
	{0x18, 0x66, 0x6E, 0x7E, 0x76, 0x66, 0x66, 0x00},//9-Й
	{0x66, 0x6C, 0x78, 0x70, 0x78, 0x6C, 0x66, 0x00},//10-К
	{0x0E, 0x1E, 0x36, 0x66, 0x66, 0x66, 0x66, 0x00},//11-Л
	{0x44, 0x6C, 0x7C, 0x54, 0x44, 0x44, 0x44, 0x00},//12-М
	{0x66, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x66, 0x00},//13-Н
	{0x3C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x00},//14-О
	{0x7E, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x00},//15-П
	{0x7C, 0x66, 0x66, 0x66, 0x7C, 0x60, 0x60, 0x00},//16-Р
	{0x3C, 0x66, 0x60, 0x60, 0x60, 0x66, 0x3C, 0x00},//17-С
	{0x7E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00},//18-Т
	{0x66, 0x66, 0x66, 0x3E, 0x06, 0x66, 0x3C, 0x00},//19-У
	{0x3C, 0x5A, 0x5A, 0x5A, 0x3C, 0x18, 0x18, 0x00},//20-Ф
	{0x66, 0x66, 0x3C, 0x18, 0x3C, 0x66, 0x66, 0x00},//21-Х
	{0x6C, 0x6C, 0x6C, 0x6C, 0x7C, 0x7E, 0x06, 0x00},//22-Ц
	{0x66, 0x66, 0x66, 0x3E, 0x06, 0x06, 0x06, 0x00},//23-Ч
	{0x5A, 0x5A, 0x5A, 0x5A, 0x5A, 0x7E, 0x7E, 0x00},//24-Ш
	{0x6A, 0x6A, 0x6A, 0x6A, 0x7E, 0x7E, 0x06, 0x00},//25-Щ
	{0x62, 0x62, 0x62, 0x7A, 0x66, 0x66, 0x7A, 0x00},//26-Ы
	{0x60, 0x60, 0x60, 0x7C, 0x66, 0x66, 0x7C, 0x00},//27-Ь
	{0x38, 0x4C, 0x06, 0x3E, 0x06, 0x4C, 0x38, 0x00},//28-Э
	{0x4E, 0x5A, 0x5A, 0x7A, 0x5A, 0x5A, 0x4E, 0x00},//29-Ю
	{0x3E, 0x66, 0x66, 0x66, 0x3E, 0x36, 0x66, 0x00},//30-Я
	{0x38, 0x44, 0x4C, 0x54, 0x64, 0x44, 0x38, 0x00},//31-0
	{0x0C, 0x1C, 0x3C, 0x0C, 0x0C, 0x0C, 0x0C, 0x00},//32-1
	{0x3C, 0x66, 0x06, 0x1C, 0x30, 0x60, 0x7E, 0x00},//33-2
	{0x3C, 0x66, 0x06, 0x1C, 0x06, 0x66, 0x3C, 0x00},//34-3
	{0x0C, 0x1C, 0x2C, 0x6C, 0x7E, 0x0C, 0x0C, 0x00},//35-4
	{0x7E, 0x60, 0x7C, 0x06, 0x06, 0x66, 0x3C, 0x00},//36-5
	{0x1C, 0x30, 0x60, 0x7C, 0x66, 0x66, 0x3C, 0x00},//37-6
	{0x7E, 0x06, 0x06, 0x0C, 0x18, 0x18, 0x18, 0x00},//38-7
	{0x3C, 0x66, 0x66, 0x3C, 0x66, 0x66, 0x3C, 0x00},//39-8
	{0x3C, 0x66, 0x66, 0x3E, 0x06, 0x0C, 0x38, 0x00},//40-9
	{0x00, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x00},//41-:
	{0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x30, 0x00},//42-;
	{0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x30, 0x00},//43-,
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00},//44-.
	{0x00, 0x18, 0x18, 0x7E, 0x7E, 0x18, 0x18, 0x00},//45-+
	{0x00, 0x00, 0x00, 0x7E, 0x7E, 0x00, 0x00, 0x00},//46--
	{0x1C, 0x36, 0x36, 0x1C, 0x00, 0x00, 0x00, 0x00},//47-° - @
	{0x60, 0x30, 0x18, 0x0C, 0x18, 0x30, 0x60, 0x00},//48->
	{0x0C, 0x18, 0x30, 0x60, 0x30, 0x18, 0x0C, 0x00},//49-<
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}//50-пробел												 //50-пробел
};

void initTablo(void)
{
	cs_set();
	HAL_SPI_Transmit(&hspi2, (uint8_t*)aTxBuffer, matrix_in_tablo, 5000);
	cs_Strobe();
}

void showTablo(void)
{
	HAL_GPIO_WritePin(GPIOA, String0_Pin | String1_Pin|String2_Pin|String3_Pin | String4_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, String5_Pin|String6_Pin|String7_Pin, GPIO_PIN_SET);

	for(uint8_t tpic = 0; tpic < matrix_in_tablo; tpic++) aTxBuffer[matrix_in_tablo - 1 - tpic] = BufferTablo[stroka][tpic];
	
	HAL_SPI_Transmit(&hspi2, (uint8_t*)aTxBuffer, matrix_in_tablo, 5000);
	cs_Strobe();

	switch(stroka){
		case 0:
			HAL_GPIO_WritePin(String0_GPIO_Port, String0_Pin, GPIO_PIN_RESET);
		  	break;
		case 1:
		  	HAL_GPIO_WritePin(String1_GPIO_Port, String1_Pin, GPIO_PIN_RESET);
		  	break;
		case 2:
		  	HAL_GPIO_WritePin(String2_GPIO_Port, String2_Pin, GPIO_PIN_RESET);
		  	break;
		case 3:
			HAL_GPIO_WritePin(String3_GPIO_Port, String3_Pin, GPIO_PIN_RESET);
		  	break;
		case 4:
			HAL_GPIO_WritePin(String4_GPIO_Port, String4_Pin, GPIO_PIN_RESET);
		  	break;
		case 5:
		  	HAL_GPIO_WritePin(String5_GPIO_Port, String5_Pin, GPIO_PIN_RESET);
		  	break;
		case 6:
		  	HAL_GPIO_WritePin(String6_GPIO_Port, String6_Pin, GPIO_PIN_RESET);
		  	break;
		case 7:
		  	HAL_GPIO_WritePin(String7_GPIO_Port, String7_Pin, GPIO_PIN_RESET);
		  	break;
	}

	stroka++;
	if(stroka > 7){
    stroka = 0;
	  if(show_seven_lines < speed_ticker_line) show_seven_lines++;
  }
}

void setDiget(uint8_t num_tpic, uint8_t str, uint8_t numb_bit, _Bool bit)
{
	numb_bit = 7 - numb_bit;
	uint8_t temp = BufferTablo[str][num_tpic];
	if(bit) temp |= (1 << numb_bit);
	else temp &= ~(1 << numb_bit);
	BufferTablo[str][num_tpic] = temp;
}

void showString(uint8_t num_tpic, char* st)
{
	uint8_t kod_simv, let_num;

	for(uint8_t s = 0; st[s] != 0; s++){
		kod_simv = (uint8_t)st[s];
		if(kod_simv < 208){
			switch (kod_simv){
				case 144: case 176:
					let_num = 0;
					break;
				case 145: case 177:
					let_num = 1;
					break;
				case 146: case 178:
					let_num = 2;
					break;
				case 147: case 179:
					let_num = 3;
					break;
				case 148: case 180:
					let_num = 4;
					break;
				case 149: case 181:
					let_num = 5;
					break;
				case 150: case 182:
					let_num = 6;
					break;
				case 151: case 183:
					let_num = 7;
					break;
				case 152: case 184:
					let_num = 8;
					break;
				case 153: case 185:
					let_num = 9;
					break;
				case 154: case 186:
					let_num = 10;
					break;
				case 155: case 187:
					let_num = 11;
					break;
				case 156: case 188:
					let_num = 12;
					break;
				case 157: case 189:
					let_num = 13;
					break;
				case 158: case 190:
					let_num = 14;
					break;
				case 159: case 191:
					let_num = 15;
					break;
				case 160: case 128:
					let_num = 16;
					break;
				case 161: case 129:
					let_num = 17;
					break;
				case 162: case 130:
					let_num = 18;
					break;
				case 163: case 131:
					let_num = 19;
					break;
				case 164: case 132:
					let_num = 20;
					break;
				case 165: case 133:
					let_num = 21;
					break;
				case 166: case 134:
					let_num = 22;
					break;
				case 167: case 135:
					let_num = 23;
					break;
				case 168: case 136:
					let_num = 24;
					break;
				case 169: case 137:
					let_num = 25;
					break;
				case 171: case 139:
					let_num = 26;
					break;
				case 172: case 140:
					let_num = 27;
					break;
				case 173: case 141:
					let_num = 28;
					break;
				case 174: case 142:
					let_num = 29;
					break;
				case 175: case 143:
					let_num = 30;
					break;
				case 48:
					let_num = 31;
					break;
				case 49:
					let_num = 32;
					break;
				case 50:
					let_num = 33;
					break;
				case 51:
					let_num = 34;
					break;
				case 52:
					let_num = 35;
					break;
				case 53:
					let_num = 36;
					break;
				case 54:
					let_num = 37;
					break;
				case 55:
					let_num = 38;
					break;
				case 56:
					let_num = 39;
					break;
				case 57:
					let_num = 40;
					break;
				case 58:
					let_num = 41;
					break;
				case 59:
					let_num = 42;
					break;
				case 44:
					let_num = 43;
					break;
				case 46:
					let_num = 44;
					break;
				case 43:
					let_num = 45;
					break;
				case 45:
					let_num = 46;
					break;
				case 32:
					let_num = 50;
					break;
				case 64:
					let_num = 47;
					break;
				case 60:
					let_num = 49;
					break;
				case 62:
					let_num = 48;
					break;
			}

			if(if_ticker) for(uint8_t lin = 0; lin < 8; lin++) BufferTabloTicker[lin][num_tpic] = letters_and_numbers[let_num][lin];
			else	for(uint8_t lin = 0; lin < 8; lin++) BufferTablo[lin][num_tpic] = letters_and_numbers[let_num][lin];
			num_tpic = sortTPIC(num_tpic);
		}
	}
}

uint8_t sortTPIC(uint8_t current_tpic)
{
	uint8_t next_tpic;
	next_tpic = current_tpic + numbers_line_matrix;
	return next_tpic;
}

void offTablo(void)
{
	for(uint8_t str = 0; str < 8; str++)
		for(uint8_t tpic = 0; tpic < matrix_in_tablo; tpic++)
			BufferTablo[str][tpic] = 0x00;
}

void onTablo(void)
{
	for(uint8_t str = 0; str < 8; str++)
		for(uint8_t tpic = 0; tpic < matrix_in_tablo; tpic++)
			BufferTablo[str][tpic] = 0xFF;
}

void degree_output(uint8_t num_tpic)//вывод градуса
{
	for(int x = 0; x < 8; x++){
			BufferTablo[x][num_tpic] = letters_and_numbers[47][x];
	}
}

void setTicker(uint8_t num_tpic, char* st)
{
	if_ticker = 1;
	showString(num_tpic, st);
	if_ticker = 0;
}

void showTicker(uint8_t num_tpic_start, uint8_t num_tpic_stop)
{
  if(temp_line){
    if(temp_line1 == 255){
      temp_line1 = num_tpic_start;
      count_line++;
    }
    else if(temp_line2 == 255  && num_tpic_start != temp_line1){
      temp_line2 = num_tpic_start;
      count_line++;
    }
    else if(temp_line3 == 255 && num_tpic_start != temp_line1 && num_tpic_start != temp_line2){
      temp_line3 = num_tpic_start;
      count_line++;
      temp_line = 0;
    }
    else temp_line = 0;
  }
    
	if(show_seven_lines >= speed_ticker_line){
		uint8_t tota_number_shifts;
	  uint8_t temp1, temp2, temp_start;

	  uint8_t num_line_shift = num_tpic_start + numbers_line_matrix;
		num_line_shift = num_line_shift % numbers_line_matrix;

		uint8_t sdv = num_shift_ticker[num_line_shift] / 8;

	  sdv *= numbers_line_matrix;
		tota_number_shifts = totalNumberShifts(num_tpic_start, num_tpic_stop);
		temp_start = num_tpic_start % numbers_line_matrix;
		
		for(uint8_t num_s = 0; num_s < 8; num_s++){
			for(uint8_t tpic = temp_start; tpic < matrix_in_tablo; tpic += numbers_line_matrix){
			    temp1 = BufferTabloTicker[num_s][tpic + sdv];
			    temp2 = BufferTabloTicker[num_s][tpic + sdv + numbers_line_matrix];
				BufferTablo[num_s][tpic] = shift_byte(temp1, temp2, num_line_shift);
			}
		}
		
		num_shift_ticker[num_line_shift]++;
		if(num_shift_ticker[num_line_shift] > tota_number_shifts) num_shift_ticker[num_line_shift] = 0;
		
		count_line_ticker++;
		if(count_line_ticker == count_line){
		  show_seven_lines = 0;
		  count_line_ticker = 0;
		}
	}
}

uint8_t totalNumberShifts(uint8_t num_tpic_start, uint8_t num_tpic_stop)
{
	uint8_t temp3, temp4, temp5, temp6;
	int ret;

	temp3 = num_tpic_start / numbers_line_matrix;
	temp4 = (num_tpic_stop / numbers_line_matrix) + 1;
	temp5 = temp4 - temp3;
	temp6 = temp5 * 8;
	temp3 = (int)temp3;
	temp6 = (int)temp6;
	ret = (temp6 - 40) + (temp3 * 8);
	if(ret <= 0) ret = 0;
	return ret;
}

uint8_t shift_byte(uint8_t first_byte, uint8_t second_byte, uint8_t n_l_s)
{
	uint8_t sdvig = num_shift_ticker[n_l_s] % 8;
	
	first_byte <<= sdvig;
	second_byte = second_byte >> (8 - sdvig);
	first_byte |= second_byte;
	return first_byte;
}

void resetTicker(void)
{
  offTablo();
  offTicker();
  num_shift_ticker[0] = 0;
  num_shift_ticker[1] = 0;
  num_shift_ticker[2] = 0;
  show_seven_lines = 0;
  count_line_ticker = 0;
  
  count_line = 0;
  temp_line1 = 255;
  temp_line2 = 255;
  temp_line3 = 255;
  temp_line = 1;
}

void offTicker(void)
{
  for(uint8_t str = 0; str < 8; str++)
		for(uint8_t tpic = 0; tpic < 153; tpic++)
			BufferTabloTicker[str][tpic] = 0x00;
}
