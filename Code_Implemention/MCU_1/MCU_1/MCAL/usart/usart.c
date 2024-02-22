/*
 * usart.c
 *
 * Created: 5/1/2023 7:35:51 AM
 *  Author: Mohamed Abdel-Wahab
 *	EMAIL : mohamedhegay22@gmail.com
 */ 
#include "usart.h"


#define READY_DONE_SENDING_SINGLE_BYTE			 2u
#define READY_TO_SEND_FIRST_BYTE				 1u
#define SENDING_BYTE							 0u
#define SENDING_MULTIBLE_BYTE					 3u
#define SENDING_SINGLE_BYTE						 4u

#define READY_DONE_RECIEVE_SINGLE_BYTE			 2u
#define READY_TO_RECIEVE_FIRST_BYTE				 1u
#define RECIEVING_BYTE							 0u
#define RECIEVING_MULTIBLE_BYTE					 3u
#define RECIEVING_SINGLE_BYTE					 4u


static volatile uint8_t u8_sg_readyToSend         = SENDING_SINGLE_BYTE;

static volatile uint8_t u8_sg_readyToSRecive =  RECIEVING_SINGLE_BYTE ;

static volatile uint8_t u8Arr_sg_dataTransimted[DATA_TO_SEND_MAX_BUFFER];
static volatile uint8_t u8Arr_sg_dataRecieved[DATA_TO_RECIVE_MAX_BUFFER];

static volatile sint8_t u8_sg_TxDatadFront_index;
static volatile uint8_t u8_sg_TxDatadRear_index;

static volatile uint8_t u8_sg_RxDatadFront_index;
static volatile uint8_t u8_sg_RxDatadRear_index;


static volatile uint8_t u8_sg_doneSendingString=0;
static volatile uint8_t u8_sg_doneRecieveString=0;

static volatile uint16_t u16_sg_stringSizeForTx=0;
static volatile uint16_t u16_sg_stringSizeForRx=0;


/* Global pointers to function to hold the address of the call back function in the upper layers */
static Fptr_usartCallBack_t sg_Tx_callBackPtr = NULL;
static Fptr_usartCallBack_t sg_Rx_callBackPtr = NULL;

ISR(USART_TXC_vect)
{
	if(sg_Tx_callBackPtr)
	{
		sg_Tx_callBackPtr();
	}
	else
	{
		// do nothing
	}
	
	UDR= u8Arr_sg_dataTransimted[u8_sg_TxDatadFront_index];
	u8_sg_TxDatadFront_index++;
	if(u8_sg_TxDatadFront_index>DATA_TO_SEND_MAX_BUFFER-1 || u8_sg_TxDatadRear_index>DATA_TO_SEND_MAX_BUFFER-1)
	{
		u8_sg_TxDatadFront_index = ZERO_INIT;
		u8_sg_TxDatadRear_index  = ZERO_INIT;
	}
	else
	{
		// do nothing
	}	
	if(((u8_sg_readyToSend==SENDING_SINGLE_BYTE) && (u8Arr_sg_dataTransimted[u8_sg_TxDatadFront_index]=='\0')) ||( (u8_sg_readyToSend==SENDING_MULTIBLE_BYTE) && u8_sg_TxDatadFront_index >= u16_sg_stringSizeForTx))
	{
		DISABLE_TX_INTERRUPT();
	}
	else
	{
		// do nothing
	}
	
}

ISR(USART_RXC_vect)
{
	if(sg_Rx_callBackPtr)
	{
		sg_Rx_callBackPtr();
	}
	else
	{
		// do nothing
	}
	if(u8_sg_RxDatadFront_index < u16_sg_stringSizeForRx)
	{
		u8Arr_sg_dataRecieved[u8_sg_RxDatadFront_index]= UDR;
		u8_sg_RxDatadFront_index++;
	}
	else
	{
		u8_sg_doneRecieveString=1;
		u8_sg_RxDatadFront_index;
		DISABLE_RX_INTERRUPT();
	}
	
	if(u8_sg_RxDatadFront_index>DATA_TO_RECIVE_MAX_BUFFER-1 || u8_sg_RxDatadRear_index>DATA_TO_RECIVE_MAX_BUFFER-1)
	{
		u8_sg_RxDatadFront_index = ZERO_INIT;
		u8_sg_RxDatadRear_index  = ZERO_INIT;
	}
	else
	{
		// do nothing
	}	
		
}


u8_usartErorrState_t USART_init(const st_usart_config_t *stPtr_a_usartConfig)
{
	u8_usartErorrState_t l_ret = USART_E_OK;
	float32_t f32_l_baudRatePrescaler;
	if(NULL==stPtr_a_usartConfig || stPtr_a_usartConfig->usartMode >= USART_INVALID_MODE || stPtr_a_usartConfig->usartDataSize >= USART_INVALID_BIT_DATA
	|| stPtr_a_usartConfig->usartParityBit >= USART_INVALID_PARITY_BIT || stPtr_a_usartConfig->usartStopBitNum >= USART_INVALID_STOP_BITS)
	{
		l_ret = USART_E_NOK;
	}
	else
	{
		/*calculate the value on UBRR -high & low- with the defined baudRate */
		
		switch(stPtr_a_usartConfig->usartMode)
		{
			case USART_ASYNCHRONOUS_NORMAL_SPEED_MODE :
				f32_l_baudRatePrescaler =  ( F_CPU / ((stPtr_a_usartConfig->usartBaudRate) * 16.0))  - 1;
				 UBRRH = (uint8_t)(((uint32_t)f32_l_baudRatePrescaler) >> 8);
				 UBRRL = (uint8_t)((uint32_t)f32_l_baudRatePrescaler);	
				break;
			case USART_ASYNCHRONOUS_DOUBLE_SPEED_MODE :
				f32_l_baudRatePrescaler =  ( F_CPU / ((stPtr_a_usartConfig->usartBaudRate) * 8.0) ) - 1;
				UBRRH = (uint8_t)(((uint32_t)f32_l_baudRatePrescaler) >> 8);
				UBRRL = (uint8_t)((uint32_t)f32_l_baudRatePrescaler);	
				break;		
			default:
				l_ret = USART_E_NOK;
				break;
		}
		/*The URSEL-BIT must be one when writing on UCSRC register*/
		SET_BIT(UCSRC,URSEL);
		/*set USART mode*/
		switch(stPtr_a_usartConfig->usartMode)
		{
			case USART_ASYNCHRONOUS_NORMAL_SPEED_MODE :
				//CLEAR UMSEL BIT TO SELECT ASYNCHRONOUS MODE
				CLEAR_BIT(UCSRC,UMSEL);
				break;
			case USART_ASYNCHRONOUS_DOUBLE_SPEED_MODE :
				//CLEAR UMSEL BIT TO SELECT ASYNCHRONOUS MODE
				CLEAR_BIT(UCSRC,UMSEL);
				//SET THE U2X TO DOUBLE THE USART TRANSMISSION SPEED
				SET_BIT(UCSRA,U2X);
				break;
			case USART_SYNCHRONOUS_MODE :
				//SET UMSEL BIT TO SELECT SYNCHRONOUS MODE
				SET_BIT(UCSRC,UMSEL);
				//SELCET THE CLOCK POLARITY IN CASE OF SYNCHRONOUS MODE ONLY 
				if((stPtr_a_usartConfig->usartTxClkPolarity==USART_SYNCHRONOUS_TX_RISING_XCK_EDGE)||
				   (stPtr_a_usartConfig->usartRxClkPolarity==USART_SYNCHRONOUS_RX_FALLING_XCK_EDGE))
				{
					CLEAR_BIT(UCSRC,UCPOL);
				}
				else if((stPtr_a_usartConfig->usartTxClkPolarity==USART_SYNCHRONOUS_TX_FALLING_XCK_EDGE)||
						(stPtr_a_usartConfig->usartRxClkPolarity==USART_SYNCHRONOUS_RX_RISING_XCK_EDGE))
				{
					SET_BIT(UCSRC,UCPOL);
				}
				else
				{
					l_ret = USART_E_NOK;
				}
				
				break;
			default:
				l_ret = USART_E_NOK;
				break;		
		}
		/*enable transmitter if set*/
		if(stPtr_a_usartConfig->usartTxEnable==USART_TX_ENABLE)
		{
			SET_BIT(UCSRB,TXEN);
		}
		else
		{
			//do nothing
		}
		
		/*enable receiver if set*/
		if(stPtr_a_usartConfig->usartRxEnable==USART_RX_ENABLE)
		{
			SET_BIT(UCSRB,RXEN);
		}
		else
		{
			//do nothing
		}
		
		
		/*adjust frame format*/
		
		//Select Number of stop-bit either one or two
		switch(stPtr_a_usartConfig->usartStopBitNum)
		{
			case USART_ONE_STOP_BIT:
				CLEAR_BIT(UCSRC,USBS);
				break;
			case USART_TWO_STOP_BITS:
				SET_BIT(UCSRC,USBS);
				break;
			default:
				l_ret = USART_E_NOK;
				break;
		}
		
		//Select Parity mode or disabled parity
		switch(stPtr_a_usartConfig->usartParityBit)
		{
			case USART_DISABLED_PARITY_BIT:
				CLEAR_BIT(UCSRC,UPM0);
				CLEAR_BIT(UCSRC,UPM1);
				break;
			case USART_EVEN_PARITY_BIT:
				CLEAR_BIT(UCSRC,UPM0);
				SET_BIT(UCSRC,UPM1);
				break;
			case USART_ODD_PARITY_BIT:
				SET_BIT(UCSRC,UPM0);
				SET_BIT(UCSRC,UPM1);
				break;
			default:
				l_ret = USART_E_NOK;
				break;
		}
		//Select the data-bit number
		switch(stPtr_a_usartConfig->usartDataSize)
		{
			case USART_FIVE_BIT_DATA:
				CLEAR_BIT(UCSRC,UCSZ0);
				CLEAR_BIT(UCSRC,UCSZ1);
				CLEAR_BIT(UCSRB,UCSZ2);
				break;
			case USART_SIX_BIT_DATA:
				SET_BIT(UCSRC,UCSZ0);
				CLEAR_BIT(UCSRC,UCSZ1);
				CLEAR_BIT(UCSRB,UCSZ2);
				break;
			case USART_SEVEN_BIT_DATA:
				CLEAR_BIT(UCSRC,UCSZ0);
				SET_BIT(UCSRC,UCSZ1);
				CLEAR_BIT(UCSRB,UCSZ2);
				break;
			case USART_EIGHT_BIT_DATA:
				SET_BIT(UCSRC,UCSZ0);
				SET_BIT(UCSRC,UCSZ1);
				CLEAR_BIT(UCSRB,UCSZ2);
				break;
			case USART_NINE_BIT_DATA:
				SET_BIT(UCSRC,UCSZ0);
				SET_BIT(UCSRC,UCSZ1);
				SET_BIT(UCSRB,UCSZ2);
				break;
			default:
				l_ret = USART_E_NOK;
				break;
		}
		//clear the data register
		CLEAR_REG(UDR);	
	}
	return l_ret;
}


u8_usartErorrState_t USART_DeInit(const st_usart_config_t *stPtr_a_usartConfig)
{
	u8_usartErorrState_t l_ret = USART_E_OK;
	if(NULL==stPtr_a_usartConfig || stPtr_a_usartConfig->usartMode >= USART_INVALID_MODE || stPtr_a_usartConfig->usartDataSize >= USART_INVALID_BIT_DATA
	|| stPtr_a_usartConfig->usartParityBit >= USART_INVALID_PARITY_BIT || stPtr_a_usartConfig->usartStopBitNum >= USART_INVALID_STOP_BITS)
	{
		l_ret = USART_E_NOK;
	}
	else
	{
		switch(stPtr_a_usartConfig->usartMode)
		{
			case USART_ASYNCHRONOUS_NORMAL_SPEED_MODE :
			
			case USART_ASYNCHRONOUS_DOUBLE_SPEED_MODE :
				 CLEAR_REG(UBRRL);
				 CLEAR_REG(UBRRH);
				 // Reset UART speed
				 CLEAR_BIT(UCSRA,U2X);
				break;
			case USART_SYNCHRONOUS_MODE :
				//SET UMSEL BIT TO SELECT SYNCHRONOUS MODE
				CLEAR_BIT(UCSRC,UMSEL);
				//SELCET THE CLOCK POLARITY IN CASE OF SYNCHRONOUS MODE ONLY 
				break;
			default:
				l_ret = USART_E_NOK;
				break;		
		}
		/*Disable transmitter if set*/
		if(stPtr_a_usartConfig->usartTxEnable==USART_TX_ENABLE)
		{
			CLEAR_BIT(UCSRB,TXEN);
		}
		else
		{
			//do nothing
		}
		
		/*Disable receiver if set*/
		if(stPtr_a_usartConfig->usartRxEnable==USART_RX_ENABLE)
		{
			CLEAR_BIT(UCSRB,RXEN);
		}
		else
		{
			//do nothing
		}
		if(stPtr_a_usartConfig->usartRxInterrupt==USART_RX_INTERRUPT_ENABLE)
		{
			DISABLE_RX_INTERRUPT();
		}
		else if(stPtr_a_usartConfig->usartTxInterrupt==USART_TX_INTERRUPT_ENABLE)
		{
			DISABLE_TX_INTERRUPT();
			
		}
		else
		{
			l_ret = USART_E_NOK;
		}
		// clear the tx and rx buffers
		memset(u8Arr_sg_dataTransimted,ZERO,DATA_TO_SEND_MAX_BUFFER);
		memset(u8Arr_sg_dataRecieved,ZERO,DATA_TO_RECIVE_MAX_BUFFER);

	}
	return l_ret;
}


u8_usartErorrState_t USART_sendData(const st_usart_config_t *stPtr_a_usartConfig ,  uint8_t u8_a_data)
{
	u8_usartErorrState_t l_ret = USART_E_OK;
	if(NULL==stPtr_a_usartConfig || stPtr_a_usartConfig->usartMode >= USART_INVALID_MODE || stPtr_a_usartConfig->usartDataSize >= USART_INVALID_BIT_DATA
	|| stPtr_a_usartConfig->usartParityBit >= USART_INVALID_PARITY_BIT || stPtr_a_usartConfig->usartStopBitNum >= USART_INVALID_STOP_BITS)
	{
		l_ret = USART_E_NOK;
	}
	else
	{
		if(stPtr_a_usartConfig->usartTxInterrupt==USART_TX_INTERRUPT_DISABLE)
		{
			/*if not using interrupt then will use blocking technique*/
			// UDRE flag is set when the Tx buffer (UDR) is empty and ready for transmitting a new byte so wait until this flag is set to one
			while(!READ_BIT(UCSRA,UDRE));
			UDR = u8_a_data;
		}
		else if(stPtr_a_usartConfig->usartTxInterrupt==USART_TX_INTERRUPT_ENABLE)
		{
			ENABLE_TX_INTERRUPT();
			u8_sg_readyToSend = SENDING_SINGLE_BYTE;
			/*when Tx buffer (UDR) is empty and ready for transmitting a new byte so wait until this flag is set to one and will generate an interrupt*/
			
			u8Arr_sg_dataTransimted[u8_sg_TxDatadRear_index] = u8_a_data ;	
			u8_sg_TxDatadRear_index++;		
			
		}
		else
		{
			l_ret = USART_E_NOK;
		}
	}
	return l_ret;
}


u8_usartErorrState_t USART_reciveData(const st_usart_config_t *stPtr_a_usartConfig , uint8_t *const u8Ptr_a_data)
{
	u8_usartErorrState_t l_ret = USART_E_OK;
	
	if(NULL==stPtr_a_usartConfig||NULL==u8Ptr_a_data || stPtr_a_usartConfig->usartMode >= USART_INVALID_MODE || stPtr_a_usartConfig->usartDataSize >= USART_INVALID_BIT_DATA
	|| stPtr_a_usartConfig->usartParityBit >= USART_INVALID_PARITY_BIT || stPtr_a_usartConfig->usartStopBitNum >= USART_INVALID_STOP_BITS)
	{
		l_ret = USART_E_NOK;
	}
	else
	{
		if(stPtr_a_usartConfig->usartRxInterrupt==USART_RX_INTERRUPT_DISABLE)
		{
			/*if not using interrupt then will use blocking technique*/
			//RXC flag is set when the UART receive data so wait until this flag is set to one
			while(!READ_BIT(UCSRA,RXC));
			*u8Ptr_a_data = UDR;
		}
		else if(stPtr_a_usartConfig->usartRxInterrupt==USART_RX_INTERRUPT_ENABLE)
		{
			ENABLE_RX_INTERRUPT();
			u8_sg_readyToSRecive = RECIEVING_SINGLE_BYTE;
			*u8Ptr_a_data = u8Arr_sg_dataRecieved[u8_sg_RxDatadRear_index];
			u8_sg_RxDatadRear_index++;
			//u8_sg_oneByteRecievingState=READY_TO_RECIEVE_FIRST_BYTE;		
		}
		else
		{
			l_ret = USART_E_NOK;
		}
	}
	return l_ret;	
}

u8_usartErorrState_t USART_sendString(const st_usart_config_t *stPtr_a_usartConfig , uint8_t *u8Arr_a_stringOfData , uint16_t u16_a_stringSize)
{
	u8_usartErorrState_t l_ret = USART_E_OK;
	 uint8_t u8_l_index=U8_ZERO_INITIALIZE;
	
	if(NULL==stPtr_a_usartConfig||NULL==u8Arr_a_stringOfData || stPtr_a_usartConfig->usartMode >= USART_INVALID_MODE || stPtr_a_usartConfig->usartDataSize >= USART_INVALID_BIT_DATA
	|| stPtr_a_usartConfig->usartParityBit >= USART_INVALID_PARITY_BIT || stPtr_a_usartConfig->usartStopBitNum >= USART_INVALID_STOP_BITS)
	{
		l_ret = USART_E_NOK;
	}
	else
	{
		if(stPtr_a_usartConfig->usartTxInterrupt==USART_TX_INTERRUPT_DISABLE)
		{
			while(u8_l_index < u16_a_stringSize  && u8Arr_a_stringOfData[u8_l_index] != '\0')
			{
				l_ret = USART_sendData(stPtr_a_usartConfig,u8Arr_a_stringOfData[u8_l_index]);
				u8_l_index++;
			}
		}
		else if(stPtr_a_usartConfig->usartRxInterrupt==USART_TX_INTERRUPT_ENABLE)
		{
			ENABLE_TX_INTERRUPT();
			u16_sg_stringSizeForTx=u16_a_stringSize;
			u8_sg_readyToSend = SENDING_MULTIBLE_BYTE;
			while(u8_l_index < u16_a_stringSize)
			{
				//l_ret = USART_sendData(stPtr_a_usartConfig,u8Arr_a_stringOfData[u8_l_index]);
				
				u8Arr_sg_dataTransimted[u8_sg_TxDatadRear_index] = u8Arr_a_stringOfData[u8_l_index] ;
				u8_sg_TxDatadRear_index++;
				u8_l_index++;
			}
			
		}	
	}
	return l_ret;
}

u8_usartErorrState_t USART_reciveString(const st_usart_config_t *stPtr_a_usartConfig ,uint8_t *const u8Arr_a_stringOfData , uint16_t u16_a_stringSize)
{
		u8_usartErorrState_t l_ret = USART_E_OK;
		uint8_t u8_l_index=U8_ZERO_INITIALIZE;
		//uint8_t u8_l_breakloopFalg=U8_ZERO_INITIALIZE;
		
		if(NULL==stPtr_a_usartConfig||NULL==u8Arr_a_stringOfData || stPtr_a_usartConfig->usartMode >= USART_INVALID_MODE || stPtr_a_usartConfig->usartDataSize >= USART_INVALID_BIT_DATA
		|| stPtr_a_usartConfig->usartParityBit >= USART_INVALID_PARITY_BIT || stPtr_a_usartConfig->usartStopBitNum >= USART_INVALID_STOP_BITS)
		{
			l_ret = USART_E_NOK;
		}
		else
		{
			if(stPtr_a_usartConfig->usartTxInterrupt==USART_TX_INTERRUPT_DISABLE)
			{
				while(u8_l_index < u16_a_stringSize  && u8Arr_a_stringOfData[u8_l_index] != '\0')
				{
					l_ret = USART_reciveData(stPtr_a_usartConfig,&u8Arr_a_stringOfData[u8_l_index]);
					u8_l_index++;
				}
			}
			else if(stPtr_a_usartConfig->usartRxInterrupt==USART_TX_INTERRUPT_ENABLE)
			{
				ENABLE_RX_INTERRUPT();
				u8_sg_readyToSRecive = RECIEVING_MULTIBLE_BYTE;
				u16_sg_stringSizeForRx=u16_a_stringSize;
				if(u8_sg_doneRecieveString)
				{
					u8_sg_RxDatadRear_index=ZERO_INIT;
					while(  u8_l_index < u16_a_stringSize)
					{			
						u8Arr_a_stringOfData[u8_l_index] = u8Arr_sg_dataRecieved[u8_sg_RxDatadRear_index] ;
						u8_sg_RxDatadRear_index++;
						u8_l_index++;
					}
					u8_sg_doneRecieveString=ZERO_INIT;
				}
			}
		}
		return l_ret;
}

u8_usartErorrState_t USART_setCallBackTx( Fptr_usartCallBack_t Fptr_a_TxCallBack)
{
	u8_usartErorrState_t l_ret = USART_E_OK;
	if(Fptr_a_TxCallBack)
	{
		sg_Tx_callBackPtr = Fptr_a_TxCallBack;
	}
	else
	{
		l_ret = USART_E_NOK;
	}
	return l_ret;
}

u8_usartErorrState_t USART_setCallBackRx( Fptr_usartCallBack_t Fptr_a_RxCallBack)
{
	u8_usartErorrState_t l_ret = USART_E_OK;
	if(Fptr_a_RxCallBack)
	{
		sg_Rx_callBackPtr = Fptr_a_RxCallBack;
	}
	else
	{
		l_ret = USART_E_NOK;
	}
	return l_ret;
}