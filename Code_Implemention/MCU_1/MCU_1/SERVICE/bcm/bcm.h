/*
 * bcm.h
 *
 * Created: 5/19/2023 5:24:28 PM
 *  Author: Mcs
 */ 


#ifndef BCM_H_
#define BCM_H_

#include "../../MCAL/usart/usart.h"

	// typedef  void (*Fptr_bcmtCallBack_t) (uint16_t u16_a_sizeOfData);
	typedef  void (*Fptr_bcmtCallBack_t) (void);


	typedef enum {
		BCM_E_OK=0,
		BCM_E_NOK=2,
		}enu_system_status_t;
	typedef enum {
		BCM_USART_BUS=0,
		BCM_SPI_BUS,
		BCM_TWI_BUS,
		BCM_INVALID_BUS_ID
	}enu_bcm_busID_t;

	 typedef enum {
 		BCM_TRANSIMTER=0,
 		BCM_RECIEVER,
 		BCM_TRANSIMTER_RECIEVER,
		BCM_INVALID_OBERATION
	 }enu_bcm_operation_t;

	typedef struct{
		enu_bcm_busID_t bcm_busID; //@ref enu_bcm_busID_t
		enu_bcm_operation_t bcm_operation;	//@ref enu_bcm_operation_t
		Fptr_bcmtCallBack_t  Fptr_bcmtTxCallBack;  //@ref Fptr_bcmtCallBack_t
		Fptr_bcmtCallBack_t  Fptr_bcmtRxCallBack;  //@ref Fptr_bcmtCallBack_t
		}str_bcm_inctance_t;



/*
* Description : initialize the BCM communication unit
* @param A Reference of the BCM driver's configuration structure
* @return enu_system_status_t: status of the function
* BCM_E_OK :the function done successfully
* BCM_E_NOK :the function has issues performing the function
*/
enu_system_status_t BCM_init(str_bcm_inctance_t *str_ptr_a_bcm_inctance);
/*
* Description : De-initialize the BCM communication unit
* @param A Reference of the BCM driver's configuration structure
* @return enu_system_status_t: status of the function
* BCM_E_OK :the function done successfully
* BCM_E_NOK :the function has issues performing the function
*/
enu_system_status_t BCM_deinit(str_bcm_inctance_t *str_ptr_a_bcm_inctance);
/*
* Description : Send one byte via BCM 
* @param 
*		 str_ptr_a_bcm_inctance : A Reference of the BCM driver's configuration structure
*		 u8_a_data : The data to be send
* @return enu_system_status_t: status of the function
* BCM_E_OK :the function done successfully
* BCM_E_NOK :the function has issues performing the function
*/
enu_system_status_t BCM_send(str_bcm_inctance_t *str_ptr_a_bcm_inctance , uint8_t u8_a_data);
/*
* Description : Receive one byte via BCM
* @param 
*		 str_ptr_a_bcm_inctance : A Reference of the BCM driver's configuration structure
*		 u8_a_data :  A Reference of The variable which will be store the recived byte at 
* @return enu_system_status_t: status of the function
* BCM_E_OK :the function done successfully
* BCM_E_NOK :the function has issues performing the function
*/
enu_system_status_t BCM_recieve(str_bcm_inctance_t *str_ptr_a_bcm_inctance , uint8_t *u8_a_data);
/*
* Description : Send Multiple bytes via BCM
* @param 
*		 str_ptr_a_bcm_inctance : A Reference of the BCM driver's configuration structure
*		 u8_a_data : The string to be send
*		 u16_a_stringSize : The string size
* @return enu_system_status_t: status of the function
* BCM_E_OK :the function done successfully
* BCM_E_NOK :the function has issues performing the function
*/
enu_system_status_t BCM_send_n(str_bcm_inctance_t *str_ptr_a_bcm_inctance , uint8_t *u8Arr_a_stringData, uint16_t u16_a_stringSize);
/*
* Description : receive Multiple bytes via BCM
* @param 
*		 str_ptr_a_bcm_inctance : A Reference of the BCM driver's configuration structure
*		 u8_a_data : The string to stored the string at
*		 u16_a_stringSize : The string size
* @return enu_system_status_t: status of the function
* BCM_E_OK :the function done successfully
* BCM_E_NOK :the function has issues performing the function
*/
enu_system_status_t BCM_recieve_n(str_bcm_inctance_t *str_ptr_a_bcm_inctance , uint8_t *u8Arr_a_stringData, uint16_t u16_a_stringSize);
/*
* Description : Call the Call Back function in the application after transmissions or reception is done
* @paramstr_ptr_a_bcm_inctance : A Reference of the BCM driver's configuration structure
* @return enu_system_status_t: status of the function
* BCM_E_OK :the function done successfully
* BCM_E_NOK :the function has issues performing the function
*/
enu_system_status_t BCM_setCallBack(str_bcm_inctance_t *str_ptr_a_bcm_inctance );
/*
* Description :Will execute the periodic actions and notifies the user with the needed events over a specific BCM instance
* @paramstr_ptr_a_bcm_inctance : A Reference of the BCM driver's configuration structure
* @return enu_system_status_t: status of the function
* BCM_E_OK :the function done successfully
* BCM_E_NOK :the function has issues performing the function
*/
enu_system_status_t BCM_dispatcher(str_bcm_inctance_t *str_ptr_a_bcm_inctance );


#endif /* BCM_H_ */