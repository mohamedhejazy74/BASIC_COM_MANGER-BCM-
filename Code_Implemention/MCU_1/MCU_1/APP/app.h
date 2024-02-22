/*
 * app.h
 *
 * Created: 5/27/2023 7:44:28 AM
 *  Author: Mcs
 */ 


#ifndef APP_H_
#define APP_H_

#include "../SERVICE/bcm/bcm.h"
#include "../HAL/led/led.h"


#define  TRANSMITTED_DATA_SIZE   30u
#define  RECIEVED_DATA_SIZE		 35u


void APP_init(void);

void APP_start(void);





#endif /* APP_H_ */