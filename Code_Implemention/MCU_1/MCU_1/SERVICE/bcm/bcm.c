/*
 * bcm.c
 *
 * Created: 5/19/2023 5:24:40 PM
 *  Author: Mcs
 */ 

#include "bcm.h"
#include "../../MCAL/usart/usart_config.h"

static volatile uint16_t u16_sg_stringSizeForTx;
static volatile uint16_t u16_sg_stringSizeForRx;

static volatile uint8_t u8_sg_stringDoneSending;
static volatile uint8_t u8_sg_stringDoneRecieving;
 
static volatile uint16_t u16_sg_charCountForTx;
static volatile uint16_t u16_sg_charCountForRx;

/* Global pointers to function to hold the address of the call back function in the upper layers */
static Fptr_usartCallBack_t sg_bcmTx_callBackPtr = NULL;
static Fptr_usartCallBack_t sg_bcmRx_callBackPtr = NULL;

static void bcm_Tx_handler(void)
{
	u16_sg_charCountForTx++;
	if(u16_sg_charCountForTx >= u16_sg_stringSizeForTx)
	{
		u8_sg_stringDoneSending = TRUE;
		u16_sg_charCountForTx = ZERO_INIT;
	}
}
static void bcm_Rx_handler(void)
{
	u16_sg_charCountForRx++;
	if(u16_sg_charCountForRx >= u16_sg_stringSizeForRx)
	{
		u8_sg_stringDoneRecieving = TRUE;
		u16_sg_charCountForRx = ZERO_INIT;
	}
}

enu_system_status_t BCM_init(str_bcm_inctance_t *str_ptr_a_bcm_inctance)
{
	enu_system_status_t enu_l_bcmRet=BCM_E_OK;
	if(str_ptr_a_bcm_inctance && str_ptr_a_bcm_inctance->bcm_busID < BCM_INVALID_BUS_ID)
	{
		switch(str_ptr_a_bcm_inctance->bcm_busID)
		{
			case BCM_USART_BUS:
				enu_l_bcmRet = USART_init(&st_g_usartObjForBcm);
				if(str_ptr_a_bcm_inctance->bcm_operation==BCM_TRANSIMTER || str_ptr_a_bcm_inctance->bcm_operation==BCM_TRANSIMTER_RECIEVER)
				{
					enu_l_bcmRet |= USART_setCallBackTx(bcm_Tx_handler);
				}
				else
				{
					//do nothing
				}
				if(str_ptr_a_bcm_inctance->bcm_operation==BCM_RECIEVER || str_ptr_a_bcm_inctance->bcm_operation==BCM_TRANSIMTER_RECIEVER)
				{
					enu_l_bcmRet |= USART_setCallBackRx(bcm_Rx_handler);
				}
				else
				{
					//do nothing
				}
				
				break;
			case BCM_SPI_BUS:
				// WILL HANDEL LATER
				break;
			case BCM_TWI_BUS:
				// WILL HANDEL LATER
				break;
			default:
				// DO NOTHING
				break;	
		}
	}
	else
	{
		enu_l_bcmRet=BCM_E_NOK;
	}
	
	return enu_l_bcmRet;
}

enu_system_status_t BCM_deinit(str_bcm_inctance_t *str_ptr_a_bcm_inctance)
{
	enu_system_status_t enu_l_bcmRet=BCM_E_OK;
	if(str_ptr_a_bcm_inctance && str_ptr_a_bcm_inctance->bcm_busID < BCM_INVALID_BUS_ID)
	{
		switch(str_ptr_a_bcm_inctance->bcm_busID)
		{
			case BCM_USART_BUS:
				enu_l_bcmRet = USART_DeInit(&st_g_usartObjForBcm);			
				break;
			case BCM_SPI_BUS:
				// WILL HANDEL LATER
				break;
			case BCM_TWI_BUS:
				// WILL HANDEL LATER
				break;
			default:
				// DO NOTHING
				break;	
		}
	}
	else
	{
		enu_l_bcmRet=BCM_E_NOK;
	}
	
	return enu_l_bcmRet;
}

enu_system_status_t BCM_send(str_bcm_inctance_t *str_ptr_a_bcm_inctance , uint8_t u8_a_data)
{
	
	enu_system_status_t enu_l_bcmRet=BCM_E_OK;
	if(str_ptr_a_bcm_inctance && str_ptr_a_bcm_inctance->bcm_busID < BCM_INVALID_BUS_ID)
	{
		switch(str_ptr_a_bcm_inctance->bcm_busID)
		{
			case BCM_USART_BUS:
				enu_l_bcmRet = USART_sendData(&st_g_usartObjForBcm,u8_a_data);
				break;
			case BCM_SPI_BUS:
				// WILL HANDEL LATER
				break;
			case BCM_TWI_BUS:
				// WILL HANDEL LATER
				break;
			default:
				// DO NOTHING
				break;	
		}
	}
	else
	{
		enu_l_bcmRet=BCM_E_NOK;
	}
	
	return enu_l_bcmRet;
}

enu_system_status_t BCM_recieve(str_bcm_inctance_t *str_ptr_a_bcm_inctance , uint8_t *u8_a_data)
{
	
	enu_system_status_t enu_l_bcmRet=BCM_E_OK;
	if(str_ptr_a_bcm_inctance && str_ptr_a_bcm_inctance->bcm_busID < BCM_INVALID_BUS_ID)
	{
		switch(str_ptr_a_bcm_inctance->bcm_busID)
		{
			case BCM_USART_BUS:
				enu_l_bcmRet = USART_reciveData(&st_g_usartObjForBcm,u8_a_data);
				break;
			case BCM_SPI_BUS:
				// WILL HANDEL LATER
				break;
			case BCM_TWI_BUS:
				// WILL HANDEL LATER
				break;
			default:
				// DO NOTHING
				break;
		}
	}
	else
	{
		enu_l_bcmRet=BCM_E_NOK;
	}
	
	return enu_l_bcmRet;
}

enu_system_status_t BCM_send_n(str_bcm_inctance_t *str_ptr_a_bcm_inctance , uint8_t *u8Arr_a_stringData, uint16_t u16_a_stringSize)
{
		enu_system_status_t enu_l_bcmRet=BCM_E_OK;
		if(str_ptr_a_bcm_inctance && u8Arr_a_stringData && str_ptr_a_bcm_inctance->bcm_busID < BCM_INVALID_BUS_ID)
		{
			switch(str_ptr_a_bcm_inctance->bcm_busID)
			{
				case BCM_USART_BUS:
					u16_sg_stringSizeForTx = u16_a_stringSize;
					enu_l_bcmRet = USART_sendString(&st_g_usartObjForBcm,u8Arr_a_stringData,u16_a_stringSize);
					break;
				case BCM_SPI_BUS:
					// WILL HANDEL LATER
					break;
				case BCM_TWI_BUS:
					// WILL HANDEL LATER
					break;
				default:
					// DO NOTHING
					break;
			}
		}
		else
		{
			enu_l_bcmRet=BCM_E_NOK;
		}
		
		return enu_l_bcmRet;
}

enu_system_status_t BCM_recieve_n(str_bcm_inctance_t *str_ptr_a_bcm_inctance , uint8_t *u8Arr_a_stringData, uint16_t u16_a_stringSize)
{
		enu_system_status_t enu_l_bcmRet=BCM_E_OK;
		if(str_ptr_a_bcm_inctance && u8Arr_a_stringData && str_ptr_a_bcm_inctance->bcm_busID < BCM_INVALID_BUS_ID)
		{
			switch(str_ptr_a_bcm_inctance->bcm_busID)
			{
				case BCM_USART_BUS:
					u16_sg_stringSizeForRx = u16_a_stringSize;
					enu_l_bcmRet = USART_reciveString(&st_g_usartObjForBcm,u8Arr_a_stringData,u16_a_stringSize);
					break;
				case BCM_SPI_BUS:
					// WILL HANDEL LATER
					break;
				case BCM_TWI_BUS:
					// WILL HANDEL LATER
					break;
				default:
					// DO NOTHING
					break;
			}
		}
		else
		{
			enu_l_bcmRet=BCM_E_NOK;
		}
		
		return enu_l_bcmRet;
}

enu_system_status_t BCM_setCallBack(str_bcm_inctance_t *str_ptr_a_bcm_inctance )
{
	enu_system_status_t enu_l_bcmRet=BCM_E_OK;
		if(str_ptr_a_bcm_inctance  && str_ptr_a_bcm_inctance->bcm_busID < BCM_INVALID_BUS_ID)
		{
			if(str_ptr_a_bcm_inctance->bcm_operation==BCM_TRANSIMTER || str_ptr_a_bcm_inctance->bcm_operation==BCM_TRANSIMTER_RECIEVER)
			{
				sg_bcmTx_callBackPtr = str_ptr_a_bcm_inctance->Fptr_bcmtTxCallBack;
			}
			else
			{
				//do nothing
			}
			if(str_ptr_a_bcm_inctance->bcm_operation==BCM_RECIEVER || str_ptr_a_bcm_inctance->bcm_operation==BCM_TRANSIMTER_RECIEVER)
			{
				sg_bcmRx_callBackPtr = str_ptr_a_bcm_inctance->Fptr_bcmtRxCallBack;
			}
			else
			{
				//do nothing
			}
		}
		else
		{
			enu_l_bcmRet=BCM_E_NOK;
		}	
		return enu_l_bcmRet;
}

enu_system_status_t BCM_dispatcher(str_bcm_inctance_t *str_ptr_a_bcm_inctance )
{
	enu_system_status_t enu_l_bcmRet=BCM_E_OK;
		if(str_ptr_a_bcm_inctance  && str_ptr_a_bcm_inctance->bcm_busID < BCM_INVALID_BUS_ID)
		{
			switch(str_ptr_a_bcm_inctance->bcm_busID)
			{
				case BCM_USART_BUS:
					if(u8_sg_stringDoneSending==TRUE)
					{
						//when usart complete the transmission , will call the function in the app layer 
						 sg_bcmTx_callBackPtr();
						 u8_sg_stringDoneSending = FALSE;
					}
					else
					{
						// do nothing
					}
					if(u8_sg_stringDoneRecieving==TRUE)
					{
						//when usart complete the transmission , will call the function in the app layer
						sg_bcmRx_callBackPtr();
						u8_sg_stringDoneRecieving = FALSE;
					}
					else
					{
						// do nothing
					}
					break;
				case BCM_SPI_BUS:
					// WILL HANDEL LATER
					break;
				case BCM_TWI_BUS:
					// WILL HANDEL LATER
					break;
				default:
					// DO NOTHING
					break;
			}
		}
		else
		{
			enu_l_bcmRet=BCM_E_NOK;
		}
		
		return enu_l_bcmRet;
}
