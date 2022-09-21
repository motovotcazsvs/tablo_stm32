#ifndef INC_MATRIX_TABLO_TPIC_H_
#define INC_MATRIX_TABLO_TPIC_H_


#include "main.h"
#include "stm32f1xx_hal.h"

#define cs_set() HAL_GPIO_WritePin(Strobe_GPIO_Port, Strobe_Pin, GPIO_PIN_RESET)
#define cs_reset() HAL_GPIO_WritePin(Strobe_GPIO_Port, Strobe_Pin, GPIO_PIN_SET)
#define cs_Strobe() cs_reset(); cs_set()
#define matrix_in_tablo 15
#define speed_ticker_line 10 ///////////////
#define numbers_line_matrix 3

void initTablo(void);
void offTablo(void);
void onTablo(void);
void showTablo(void);
void setDiget(uint8_t num_tpic, uint8_t str, uint8_t numb_bit, _Bool bit);
void showString(uint8_t num_tpic, char* st);
uint8_t sortTPIC(uint8_t matrix);
void degree_output(uint8_t num_tpic);
void setTicker(uint8_t num_tpic, char* st);
void showTicker(uint8_t num_tpic_start, uint8_t num_tpic_stop);
uint8_t totalNumberShifts(uint8_t num_tpic_start, uint8_t num_tpic_stop);
uint8_t shift_byte(uint8_t first_byte, uint8_t second_byte, uint8_t n_l_s);
void resetTicker(void);
void offTicker(void);

#endif
