/*
 * usart_pre_compile_config.h
 *
 * Created: 5/27/2023 5:06:18 AM
 *  Author: Mcs
 */ 


#ifndef USART_PRE_COMPILE_CONFIG_H_
#define USART_PRE_COMPILE_CONFIG_H_

#ifndef	 F_CPU
# define F_CPU 8000000UL
#endif
#ifndef	 USART_CONFIG_BAUDRATE
# define USART_CONFIG_BAUDRATE		9600UL
#endif


#ifndef	 DATA_TO_SEND_MAX_BUFFER
# define DATA_TO_SEND_MAX_BUFFER	250U
#endif
#ifndef	 DATA_TO_RECIVE_MAX_BUFFER
# define DATA_TO_RECIVE_MAX_BUFFER	250U
#endif



#endif /* USART_PRE_COMPILE_CONFIG_H_ */