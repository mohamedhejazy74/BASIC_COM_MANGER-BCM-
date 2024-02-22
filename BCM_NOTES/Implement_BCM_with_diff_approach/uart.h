/**
 * @file    uart.h
 * @author  Mina Raouf (i.minaraouf@gmail.com)
 * @brief   UART Header Source
 * @version 0.1
 * @date    2023-05-30
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "common.h"

typedef enum
{
    SERIAL_COMM_MEDIUM_STATUS_IDLE          = 0     ,
    SERIAL_COMM_MEDIUM_STATUS_OPERATING             ,
    SERIAL_COMM_MEDIUM_STATUS_BUSY                  ,
    SERIAL_COMM_MEDIUM_STATUS_TOTAL
}enu_serial_comm_status_t;

enu_system_status_code_t    uart_init(uint8_t_ uint8_channel_num);
enu_system_status_code_t    uart_deinit(uint8_t_ uint8_channel_num);
enu_system_status_code_t    uart_send(uint8_t_ uint8_channel_num, uint8_t_ uint8_data_to_send);
enu_system_status_code_t    uart_send_n(uint8_t_ uint8_channel_num, uint8_t_* ptr_uint8_data_to_send, uint16_t_ uint16_buffer_length);
enu_system_status_code_t    uart_get_medium_status(enu_serial_comm_status_t* ptr_enu_serial_comm_status);
void                        uart_dispatcher(void);