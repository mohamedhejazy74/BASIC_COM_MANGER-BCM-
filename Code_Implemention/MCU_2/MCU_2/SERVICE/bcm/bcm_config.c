/*
 * bcm_config.c
 *
 * Created: 5/27/2023 5:36:49 AM
 *  Author: Mcs
 */ 
#include "bcm.h"
#include "bcm_config.h"

str_bcm_inctance_t str_g_bcm_inctance = {
	.bcm_busID = BCM_USART_BUS,
	.bcm_operation = BCM_TRANSIMTER_RECIEVER
};