/*
 * led.h
 *
 * Created: 4/5/2023 8:29:40 PM
 *  Author: Mohamed Abdel-Wahab
 */ 


#ifndef LED_H_
#define LED_H_

/**********************************  section 1: Includes ********************************************************/
#include "../../MCAL/dio/dio.h"

/**********************************  section 2: Macro Declarations ***********************************************/


/**********************************  section 3: Macro Like Function Declarations *************************** *****/


/**********************************  section 4: Data Type Declarations  ******************************************/
typedef enum{
	LED_OFF=0,
	LED_ON
}led_status_t;


typedef struct{
	pin_config_t led_pin;
	led_status_t led_status;
}led_t;
/**********************************  section 5: Function Declarations ********************************************/
/**
 * @breif  Initialize The led by configuring the pin as output and write low
 * @param Led  The reference of the led module configuration
 * @return status of the function 
 *          E_OK :the function done successfully
 *          E_NOT_OK :the function has issues performing the function 
 */
Std_ReturnType LED_initialize(const led_t *led_ptr);

/**
 * @breif Turn the led on
 * @param led  The reference of the led module configuration
 * @return status of the function 
 *          E_OK :the function done successfully
 *          E_NOT_OK :the function has issues performing the function 
 */

Std_ReturnType LED_turn_on(const led_t *led_ptr);

/**
 * @breif Turn the led off
 * @param led  The reference of the led module configuration
 * @return status of the function 
 *          E_OK :the function done successfully
 *          E_NOT_OK :the function has issues performing the function 
 */

Std_ReturnType LED_turn_off (const led_t *led_ptr);

/**
 * @breif  Toggle the led
 * @param led  The reference of the led module configuration
 * @return status of the function 
 *          E_OK :the function done successfully
 *          E_NOT_OK :the function has issues performing the function 
 */
Std_ReturnType LED_turn_toggle (const led_t *led_ptr);


#endif /* LED_H_ */