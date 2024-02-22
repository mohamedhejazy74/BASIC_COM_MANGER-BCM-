/*
 * dio.h
 *
 * Created: 4/5/2023 8:04:31 PM
 *  Author:  Mohamed Abdel-Wahab
 */ 


#ifndef DIO_H_
#define DIO_H_

/**********************************  section 1: Includes ********************************************************/
#include "../../STD_LIBRARIES/STD_TYPES.h"
#include "../../STD_LIBRARIES/bit_math.h"
#include "private_regs.h"

/**********************************  section 2: Macro Declarations ***********************************************/
#define PORT_PIN_MAX_NUMBER  8U
#define PORT_MAX_NUMBER      4U

/**********************************  section 3: Macro Like Function Declarations *************************** *****/


/**********************************  section 4: Data Type Declarations  ******************************************/
typedef enum{
	DIO_LOGIC_LOW=0,
	DIO_LOGIC_HIGH=1
}logic_t;

typedef enum{
	DIO_DIRECTION_INPUT=0,
	DIO_DIRECTION_OUTPUT,
	
}direction_t;

typedef enum{
	PIN0=0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7
}pin_index_t;

typedef enum{
	PORTA_INDEX=0,
	PORTB_INDEX,
	PORTC_INDEX,
	PORTD_INDEX,
}port_index_t;

typedef struct{
	port_index_t port ;        /* @ref port_index_t*/
	pin_index_t pin  ;         /* @ref pin_index_t*/
}pin_config_t;

/**********************************  section 5: Function Declarations ********************************************/
/**
* @brief Initialize the direction of specific pin @ref direction_t
* @param _pin_config A Reference of the pin configuration @pin_config_t
* @return status of the function
* E_OK :the function done successfully
* E_NOT_OK :the function has issues performing the function
*/
Std_ReturnType DIO_pin_direction_intialize(const pin_config_t *pin_config_ptr,direction_t a_direction);
/**
* @brief Write the logic of specific pin @ref logic_t
* @param _pin_config A Reference of the pin configuration @pin_config_t
* @param logic
* @return status of the function
* E_OK :the function done successfully
* E_NOT_OK :the function has issues performing the function
*/
Std_ReturnType DIO_pin_write_logic(const pin_config_t *pin_config_ptr,const logic_t a_logic);
/**
* @brief Read the logic of specific pin @ref logic_t
* @param _pin_config A Reference of the pin configuration @pin_config_t
* @param logic
* @return status of the function
* E_OK :the function done successfully
* E_NOT_OK :the function has issues performing the function
*/
Std_ReturnType DIO_pin_read_logic(const pin_config_t *pin_config_ptr, logic_t *logic_ptr);

/**
* @brief Toggle the logic of specific pin @ref logic_t
* @param _pin_config A Reference of the pin configuration @pin_config_t
* @return status of the function
* E_OK :the function done successfully
* E_NOT_OK :the function has issues performing the function
*/
Std_ReturnType DIO_pin_toggle_logic(const pin_config_t *pin_config_ptr);
/**
* @brief Initialize the direction of specific pin and Initialize its logic
* @param _pin_config A Reference of the pin configuration @pin_config_t
* @return status of the function
* E_OK :the function done successfully
* E_NOT_OK :the function has issues performing the function
*/
/*
Std_ReturnType DIO_pin_intialize(const pin_config_t *pin_config_ptr);
*/
/**
*
* @param port_index
* @param direction
* @return status of the function
* E_OK :the function done successfully
* E_NOT_OK :the function has issues performing the function
*/
Std_ReturnType DIO_port_direction_intialize(const port_index_t a_port_index, uint8_t a_direction);
/**
* @param port_index
* @param logic
* @return status of the function
* E_OK :the function done successfully
* E_NOT_OK :the function has issues performing the function
*/
Std_ReturnType DIO_port_write_logic(const port_index_t a_port_index , uint8_t a_logic);
/**
* @param port_index
* @param logic
* @return status of the function
* E_OK :the function done successfully
* E_NOT_OK :the function has issues performing the function
*/
Std_ReturnType DIO_port_read_logic(const port_index_t a_port_index , uint8_t *const a_logic_ptr);
/**
* @param port_index
* @return status of the function
* E_OK :the function done successfully
* E_NOT_OK :the function has issues performing the function
*/
Std_ReturnType DIO_port_toggle_logic(const port_index_t a_port_index);


#endif /* DIO_H_ */