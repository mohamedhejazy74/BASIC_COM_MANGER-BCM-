/*
 * MCU_2.c
 *
 * Created: 5/25/2023 8:40:44 PM
 * Author : Mcs
 */ 

//#include <avr/delay.h>
#include "APP/app.h"

int main(void)
{
	APP_init();
    while (TRUE) 
    {
		APP_start();		
    }
}