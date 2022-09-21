#include "PressKey.h"

extern _Bool menu_settings;
extern uint8_t min, hour, day, date, mounth, year;

uint16_t fix_ti3 = 0;
_Bool timer_off3 = 1;
uint16_t fix_ti4 = 0;
_Bool timer_off4 = 1;
uint8_t set_setting = 0;
uint8_t change_button_state = 0;
uint8_t current_state, last_state;
uint8_t change_button = 0;
_Bool Key_Settings,	Key_Nextt, Key_Previous;


void getKey(void)
{
    if(HAL_GPIO_ReadPin(KEY_SET_GPIO_Port, KEY_SET_Pin) == GPIO_PIN_SET) change_button_state |= (1 << 0);
	else change_button_state &= ~(1 << 0); 	
	
	if(HAL_GPIO_ReadPin(KEY_NEXT_GPIO_Port, KEY_NEXT_Pin) == GPIO_PIN_SET) change_button_state |= (1 << 1);
	else change_button_state &= ~(1 << 1);

	if(HAL_GPIO_ReadPin(KEY_PREV_GPIO_Port, KEY_PREV_Pin) == GPIO_PIN_SET) change_button_state |= (1 << 2);
	else change_button_state &= ~(1 << 2);
	
   	change_button = changeButtonsState();
    if(change_button && timer_off3 == 1){    	    	
    	last_state = change_button_state & 0b00000111;
    	change_button_state <<= 3;
    	
    	fix_ti3 = getCurrentTick();
        timer_off3 = 0;
    }
    else if(controlTickTime(fix_ti3, 20)){
    	timer_off3 = 1;
    	current_state = change_button_state & 0b00000111;
    	
    	if(current_state == last_state) buttonAssignment();
    	else {
    		last_state = change_button_state & 0b00000111;
			change_button_state <<= 3;
			
			timer_off3 = 0;
			fix_ti3 = getCurrentTick();
    	}
    }    
    if(timer_off3 == 1) change_button_state <<= 3;
}

uint8_t changeButtonsState(void)
{
	unsigned char ch_button;
 	
 	ch_button = change_button_state >> 3;	 
 	return (ch_button ^ (change_button_state & 0b00000111));	
}

void buttonAssignment(void)
{	
	Key_Settings = current_state & 0b00000001;	
	Key_Nextt = current_state & 0b00000010; 	
	Key_Previous = current_state & 0b00000100;
}

void controlKey()
{
	static _Bool key_next_was_pressed = 0;
	static _Bool key_previous_was_pressed = 0;
	static _Bool key_settings_was_pressed = 0;
	
    getKey();
	
	if(Key_Nextt && !key_next_was_pressed){		
		key_next_was_pressed = 1;
		stateNext();
	}
	else if(Key_Previous && !key_previous_was_pressed){		
		key_previous_was_pressed = 1;
		statePrevious();
	}
	else if(Key_Settings){
	    if(timer_off4){
            fix_ti4 = getCurrentTick();
            timer_off4 = 0;
            key_settings_was_pressed = 1;
        }
        else if(key_settings_was_pressed && controlTickTime(fix_ti4, 1000)){
        	key_settings_was_pressed = 0;
            stateOnOffSettings();
        }
	}
	else  if(!Key_Settings && key_settings_was_pressed){
        stateNextSetting();
	}

    if(!Key_Nextt) key_next_was_pressed = 0; 
    if(!Key_Previous) key_previous_was_pressed = 0;
    if(!Key_Settings){
        key_settings_was_pressed = 0;
        timer_off4 = 1;
    }
}

void stateOnOffSettings(void)
{
    menu_settings = !menu_settings;
    if(menu_settings) set_setting = 1;
}

void stateNextSetting(void)
{
    if(!menu_settings) return;
    
    set_setting++;
    if(set_setting > 6){
        set_setting = 0;
        menu_settings = 0;
    }
}

void stateNext(void)
{
    if(!menu_settings) return;
    
    switch(set_setting){
        case 1:
           hour++;
           if(hour > 23) hour = 0;
           break;
        case 2:
           min++;
           if(min > 59) min = 0;
           break;
        case 3:
            day++;
            if(day > 7) day = 1;
            break;
        case 4:
            date++;
            if(date > 31) date = 1;
            break;
        case 5:
            mounth++;
            if(mounth > 12) mounth = 1;
            break;
        case 6:
            year++;
            if(year > 99) year = 0;
            break;
    }
    setTime();
}

void statePrevious(void)
{
    if(!menu_settings) return;
    
     switch(set_setting){
        case 1:
           if(hour == 0) hour = 23;
           else hour--;
           break;
        case 2:
           if(min == 0) min = 59;
           else min--;
           break;
        case 3:
            if(day == 1) day = 7;
            else day--;
            break;
        case 4:
            if(date == 1) date = 31;
            else date--;
            break;
        case 5:
            if(mounth == 1) mounth = 12;
            else mounth--;
            break;
        case 6:
            if(year == 0) year = 99;
            else year--;
            break;
    }
     setTime();
}

uint8_t getStateNextSetting(void)
{
    return set_setting;
}

