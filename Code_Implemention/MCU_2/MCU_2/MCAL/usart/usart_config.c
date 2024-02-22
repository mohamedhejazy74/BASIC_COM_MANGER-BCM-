/*
 * usart_config.c
 *
 * Created: 5/27/2023 5:01:29 AM
 *  Author: Mcs
 */ 
 #include "usart.h"
 #include "usart_pre_compile_config.h"

 
 st_usart_config_t st_g_usartObjForBcm = {
	 .usartBaudRate=USART_CONFIG_BAUDRATE,
	 .usartDataSize = USART_EIGHT_BIT_DATA,
	 .usartMode = USART_ASYNCHRONOUS_NORMAL_SPEED_MODE,
	 .usartParityBit = USART_DISABLED_PARITY_BIT,
	 .usartRxEnable = USART_RX_ENABLE,
	 .usartTxEnable = USART_TX_ENABLE,
	 .usartRxInterrupt = USART_RX_INTERRUPT_ENABLE,
	 .usartTxInterrupt = USART_TX_INTERRUPT_ENABLE,
	 .usartStopBitNum = USART_ONE_STOP_BIT,
 };
 
 