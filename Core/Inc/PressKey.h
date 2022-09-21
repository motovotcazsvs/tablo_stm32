#ifndef INC_PRESSKEY_H_
#define INC_PRESSKEY_H_

#include "main.h"
#include "stm32f1xx_hal.h"


uint8_t changeButtonsState(void);
void getKey(void);
void controlKey(void);
void buttonAssignment(void);
void stateOnOffSettings(void);
void stateNextSetting(void);
void stateNext(void);
void statePrevious(void);
uint8_t getStateNextSetting(void);

#endif
