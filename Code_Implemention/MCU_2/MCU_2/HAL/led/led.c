/*
 * led.c
 *
 * Created: 4/5/2023 8:30:02 PM
 *  Author: Mohamed Abdel-Wahab
 */ 
#include "led.h"
Std_ReturnType LED_initialize(const led_t *led_ptr)
{
	Std_ReturnType ret = E_OK;
	if(NULL == led_ptr || (led_ptr->led_pin.pin > PORT_PIN_MAX_NUMBER-1) || (led_ptr->led_pin.port > PORT_MAX_NUMBER-1))
	{
		ret = E_NOT_OK;
	}
	else
	{
		ret = DIO_pin_direction_intialize(&(led_ptr->led_pin),DIO_DIRECTION_OUTPUT);
		switch(led_ptr->led_status)
		{
			case LED_OFF:
				ret = DIO_pin_write_logic(&(led_ptr->led_pin),DIO_LOGIC_LOW);
				break;
			case LED_ON:
				ret = DIO_pin_write_logic(&(led_ptr->led_pin),DIO_LOGIC_HIGH);
				break;
			default:
				ret = E_NOT_OK;
				break;
		}
	}
	return ret;
}

Std_ReturnType LED_turn_on(const led_t *led_ptr)
{
	Std_ReturnType ret = E_OK;
	if(NULL == led_ptr || (led_ptr->led_pin.pin > PORT_PIN_MAX_NUMBER-1) || (led_ptr->led_pin.port > PORT_MAX_NUMBER-1))
	{
		ret = E_NOT_OK;
	}
	else
	{
		ret = DIO_pin_write_logic(&(led_ptr->led_pin),DIO_LOGIC_HIGH);
	}
	return ret;
}

Std_ReturnType LED_turn_off (const led_t *led_ptr)
{
	Std_ReturnType ret = E_OK;
	if(NULL == led_ptr || (led_ptr->led_pin.pin > PORT_PIN_MAX_NUMBER-1) || (led_ptr->led_pin.port > PORT_MAX_NUMBER-1))
	{
		ret = E_NOT_OK;
	}
	else
	{
		ret = DIO_pin_write_logic(&(led_ptr->led_pin),DIO_LOGIC_LOW);
	}
	return ret;
}
Std_ReturnType LED_turn_toggle (const led_t *led_ptr)
{
	Std_ReturnType ret = E_OK;
	if(NULL == led_ptr || (led_ptr->led_pin.pin > PORT_PIN_MAX_NUMBER-1) || (led_ptr->led_pin.port > PORT_MAX_NUMBER-1))
	{
		ret = E_NOT_OK;
	}
	else
	{
		ret = DIO_pin_toggle_logic(&(led_ptr->led_pin));
	}
	return ret;
}   