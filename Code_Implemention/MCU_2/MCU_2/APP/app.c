/*
 * app.c
 *
 * Created: 5/27/2023 7:44:40 AM
 *  Author: Mcs
 */ 
#include "app.h"

#include "../SERVICE/bcm/bcm_config.h"
#include "../HAL/led/led_config.h"


static uint8_t u8Arr_sg_dataTobeSend[TRANSMITTED_DATA_SIZE]="OK,Send Confirmation TO MCU_1";
static uint8_t u8Arr_sg_dataTobeRecieved[RECIEVED_DATA_SIZE];
static uint8_t u8Arr_sg_flag;
 
static Std_ReturnType enu_sg_ret;
static void Tx_handeler(void)
{
	enu_sg_ret = LED_turn_toggle(&st_g_led0_instance);
	//_delay_ms(1000);
}
static void Rx_handeler(void)
{
	enu_sg_ret = LED_turn_toggle(&st_g_led1_instance);
	//_delay_ms(1000);
}
void APP_init(void)
{
	GLOBAL_InterruptEnable();
	enu_sg_ret = LED_initialize(&st_g_led0_instance);
	enu_sg_ret = LED_initialize(&st_g_led1_instance);
	enu_sg_ret |= BCM_init(&str_g_bcm_inctance);
	str_g_bcm_inctance.Fptr_bcmtTxCallBack=Tx_handeler;
	str_g_bcm_inctance.Fptr_bcmtRxCallBack=Rx_handeler;
	enu_sg_ret |= BCM_setCallBack(&str_g_bcm_inctance);
}


void APP_start(void)
{
	enu_sg_ret |= BCM_dispatcher(&str_g_bcm_inctance);
	if(!u8Arr_sg_flag)
	{
		enu_sg_ret |= BCM_send_n(&str_g_bcm_inctance,u8Arr_sg_dataTobeSend,TRANSMITTED_DATA_SIZE);
		u8Arr_sg_flag++;
	}
	else
	{
		//do nothing
	}
	
	enu_sg_ret |= BCM_recieve_n(&str_g_bcm_inctance,u8Arr_sg_dataTobeRecieved,RECIEVED_DATA_SIZE);
}