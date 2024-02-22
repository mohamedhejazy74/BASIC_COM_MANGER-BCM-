/*
 * led_config.c
 *
 * Created: 5/27/2023 7:01:54 AM
 *  Author: Mcs
 */ 
#include "led.h"
#include "led_config.h"


led_t st_g_led0_instance = {
	.led_pin.pin=PIN0,
	.led_pin.port=PORTB_INDEX,
	.led_status = LED_OFF
};


led_t st_g_led1_instance = {
	.led_pin.pin=PIN1,
	.led_pin.port=PORTB_INDEX,
	.led_status = LED_OFF
};