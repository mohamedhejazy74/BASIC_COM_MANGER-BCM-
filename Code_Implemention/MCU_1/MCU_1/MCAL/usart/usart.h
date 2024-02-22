/*
 * usart.h
 *
 * Created: 5/1/2023 6:54:34 AM
 *  Author: Mohamed Abdel-Wahab
 *	EMAIL : mohamedhegay22@gmail.com
 */ 


#ifndef USART_H_
#define USART_H_

/* ------------------------------------------------------- Includes ---------------------------------------------------------------------*/
#include "../../STD_LIBRARIES/STD_TYPES.h"
#include "../../STD_LIBRARIES/bit_math.h"
#include "usart_private_regs.h"
#include "usart_pre_compile_config.h"

/* ------------------------------------------------------Data Type Declarations ----------------------------------------------------------*/

typedef  void (*Fptr_usartCallBack_t) (void);

typedef uint8_t u8_usartMode_t;

typedef uint8_t u8_usartTx_enable_t;
typedef uint8_t u8_usartRx_enable_t;

typedef uint8_t u8_usartTx_interruptMask_t;
typedef uint8_t u8_usartRx_interruptMask_t;

typedef uint8_t u8_usartStopBit_t;
typedef uint8_t u8_usartParityBit_t;
typedef uint8_t u8_usartDataSize_t;

typedef uint8_t u8_usartTxClkPolarity_t;
typedef uint8_t u8_usartRxClkPolarity_t;



typedef uint8_t u8_usartErorrState_t;

typedef struct{
	u8_usartMode_t usartMode;	/*@ref u8_usartMode_t*/
	u8_usartTx_enable_t usartTxEnable;	/*@ref u8_usartTx_enable_t*/
	u8_usartTx_interruptMask_t usartTxInterrupt;	/*@ref u8_usartTx_interruptMask_t*/
	u8_usartRx_enable_t usartRxEnable;	/*@ref u8_usartRx_enable_t*/
	u8_usartRx_interruptMask_t usartRxInterrupt;	/*@ref u8_usartRx_interruptMask_t*/
	u8_usartStopBit_t usartStopBitNum;	/*@ref u8_usartStopBit_t*/
	u8_usartParityBit_t usartParityBit;	/*@ref u8_usartParityBit_t*/
	u8_usartDataSize_t usartDataSize;	/*@ref u8_usartDataSize_t*/
	u8_usartTxClkPolarity_t usartTxClkPolarity;		/*@ref u8_usartTxClkPolarity_t*/
	u8_usartRxClkPolarity_t usartRxClkPolarity;		/*@ref u8_usartRxClkPolarity_t*/
	uint32_t usartBaudRate; /*define the Buadrate value*/ 
}st_usart_config_t;	

/* ------------------------------------------------------ Macro Declarations ------------------------------------------------------------*/

/* USART Working Mode */
#define USART_ASYNCHRONOUS_NORMAL_SPEED_MODE		 ((u8_usartMode_t)0x00)
#define USART_ASYNCHRONOUS_DOUBLE_SPEED_MODE		 ((u8_usartMode_t)0x01)
#define USART_SYNCHRONOUS_MODE						 ((u8_usartMode_t)0x02)
#define USART_INVALID_MODE							 ((u8_usartMode_t)0x03)
/* USART Transmit Enable */
#define USART_TX_DISABLE		 ((u8_usartTx_enable_t)0x00)
#define USART_TX_ENABLE			 ((u8_usartTx_enable_t)0x01)
/* USART Receiver Enable */
#define USART_RX_DISABLE		 ((u8_usartRx_enable_t)0x00)
#define USART_RX_ENABLE			 ((u8_usartRx_enable_t)0x01)
/* USART Transmit Interrupt Enable Feature */
#define USART_TX_INTERRUPT_DISABLE			 ((u8_usartTx_interruptMask_t)0x00)
#define USART_TX_INTERRUPT_ENABLE			 ((u8_usartTx_interruptMask_t)0x01)
/* EUSART Receiver Interrupt Enable Feature*/
#define USART_RX_INTERRUPT_DISABLE			 ((u8_usartRx_interruptMask_t)0x00)
#define USART_RX_INTERRUPT_ENABLE			 ((u8_usartRx_interruptMask_t)0x01)
/*Select Number of stop-bit either one or two */
#define USART_ONE_STOP_BIT			 ((u8_usartStopBit_t)0x00)
#define USART_TWO_STOP_BITS			 ((u8_usartStopBit_t)0x01)
#define USART_INVALID_STOP_BITS		 ((u8_usartStopBit_t)0x02)
/*Select Parity mode or disabled parity*/
#define USART_DISABLED_PARITY_BIT	 ((u8_usartParityBit_t)0x00)
#define USART_EVEN_PARITY_BIT		 ((u8_usartParityBit_t)0x01)
#define USART_ODD_PARITY_BIT		 ((u8_usartParityBit_t)0x02)
#define USART_INVALID_PARITY_BIT	 ((u8_usartParityBit_t)0x03)
/*Select the data-bit number*/
#define USART_FIVE_BIT_DATA			 ((u8_usartDataSize_t)0x00)
#define USART_SIX_BIT_DATA			 ((u8_usartDataSize_t)0x01)
#define USART_SEVEN_BIT_DATA		 ((u8_usartDataSize_t)0x02)
#define USART_EIGHT_BIT_DATA		 ((u8_usartDataSize_t)0x03)
#define USART_NINE_BIT_DATA			 ((u8_usartDataSize_t)0x04)
#define USART_INVALID_BIT_DATA		 ((u8_usartDataSize_t)0x05)
/*SELCET THE CLOCK POLARITY IN CASE OF SYNCHRONOUS MODE ONLY */
#define USART_SYNCHRONOUS_TX_RISING_XCK_EDGE		 ((u8_usartTxClkPolarity_t)0x00)
#define USART_SYNCHRONOUS_TX_FALLING_XCK_EDGE		 ((u8_usartTxClkPolarity_t)0x01)

#define USART_SYNCHRONOUS_RX_RISING_XCK_EDGE		 ((u8_usartRxClkPolarity_t)0x00)
#define USART_SYNCHRONOUS_RX_FALLING_XCK_EDGE		 ((u8_usartRxClkPolarity_t)0x01)

/*The Error state of The USART*/	
#define USART_E_OK		 ((u8_usartErorrState_t)0x00)
#define USART_E_NOK      ((u8_usartErorrState_t)0x01)


/*AN INDICATION TO TERMINATE RECIEVING BYTES AND STORE IT IN THE CHARCTER ARRAY (ASCII OF ENTER)*/
#define END_OF_STRING_SYMPOL ((uint8_t)0x0D)
/* ------------------------------------------------------ Macro Like Functions Declarations ---------------------------------------------*/



#define  ENABLE_TX_INTERRUPT()					(SET_BIT(UCSRB,TXCIE))
#define  DISABLE_TX_INTERRUPT()					(CLEAR_BIT(UCSRB,TXCIE))

#define  ENABLE_EMPTY_DATA_REG_INTERRUPT()		(SET_BIT(UCSRB,UDRIE))
#define  DISABLE_EMPTY_DATA_REG_INTERRUPT()		(CLEAR_BIT(UCSRB,UDRIE))

#define  ENABLE_RX_INTERRUPT()					(SET_BIT(UCSRB,RXCIE))
#define  DISABLE_RX_INTERRUPT()					(CLEAR_BIT(UCSRB,RXCIE))



/* ------------------------------------------------- Software Interfaces Declarations ---------------------------------------------------*/

/*
* Description : initialize the USART driver
* @param A Reference of the USART driver's configuration structure
* @return Std_ReturnType: status of the function
* USART_E_OK :the function done successfully
* USART_E_NOK :the function has issues performing the function
*/
u8_usartErorrState_t USART_init(const st_usart_config_t *stPtr_a_usartConfig);

/*
* Description : De-initialize the USART driver
* @param A Reference of the USART driver's configuration structure
* @return Std_ReturnType: status of the function
* USART_E_OK :the function done successfully
* USART_E_NOK :the function has issues performing the function
*/
u8_usartErorrState_t USART_DeInit(const st_usart_config_t *stPtr_a_usartConfig);
/*
* Description : Send one byte via USART bus 
* @param u8_a_data : The data to be send
*		 stPtr_a_usartConfig : A Reference of the USART driver's configuration structure
* @return Std_ReturnType: status of the function
* USART_E_OK :the function done successfully
* USART_E_NOK :the function has issues performing the function
*/
u8_usartErorrState_t USART_sendData(const st_usart_config_t *stPtr_a_usartConfig ,  uint8_t u8_a_data);
/*
* Description : Receive one byte via USART bus
* @param u8Ptr_a_data: A Reference of the container of the received data
*			 stPtr_a_usartConfig:A Reference of the USART driver's configuration structure
* @return Std_ReturnType: status of the function
* USART_E_OK :the function done successfully
* USART_E_NOK :the function has issues performing the function
*/
u8_usartErorrState_t USART_reciveData(const st_usart_config_t *stPtr_a_usartConfig , uint8_t *const u8Ptr_a_data);
/*
* Description : Send string via USART bus
* @param The data string -array of characters- to be send
*			 stPtr_a_usartConfig:A Reference of the USART driver's configuration structure
* @return Std_ReturnType: status of the function
* USART_E_OK :the function done successfully
* USART_E_NOK :the function has issues performing the function
*/
u8_usartErorrState_t USART_sendString(const st_usart_config_t *stPtr_a_usartConfig , uint8_t *u8Arr_a_stringOfData , uint16_t u16_a_stringSize);
/*
* Description : Receive string via USART bus
* @param The data string -array of characters- to store the received data string
*			 stPtr_a_usartConfig:A Reference of the USART driver's configuration structure
* @return Std_ReturnType: status of the function
* USART_E_OK :the function done successfully
* USART_E_NOK :the function has issues performing the function
*/
u8_usartErorrState_t USART_reciveString(const st_usart_config_t *stPtr_a_usartConfig ,uint8_t *const u8Arr_a_stringOfData , uint16_t u16_a_stringSize);


/*
* Description : Call the Call Back function in the application after transmissions did its job
* @param A pointer to function
* @return status of the function
* USART_E_OK :the function done successfully
* USART_E_NOK :the function has issues performing the function
*/
u8_usartErorrState_t USART_setCallBackTx( Fptr_usartCallBack_t Fptr_a_TxCallBack);

/*
* Description : Call the Call Back function in the application after Reception did its job
* @param A pointer to function
* @return status of the function
* USART_E_OK :the function done successfully
* USART_E_NOK :the function has issues performing the function
*/
u8_usartErorrState_t USART_setCallBackRx( Fptr_usartCallBack_t Fptr_a_RxCallBack);


#endif /* USART_H_ */