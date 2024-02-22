/**
 * @file    :   bcm.h
 * @author  :   Mina Raouf (i.minaraouf@gmail.com)
 * @brief   :   Header File Contains all the types and Status Code For Basic Communication Manager
 * @note    :   ANY SERIAL COMMUNICATION OPERATING ON BCM SHALL SUPPORTS INTERRUPT OPERATION TO ACHIEVE MAXIMUM UTILIZATION OF THE BCM 
 * @version :   2.0
 * @date    :   2023-04-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef     __BCM_H__
#define     __BCM_H__

#include "common.h"

/*
    CONSTANT MACRO. Don't Change it!
    As there is No Send/Receive Data Length Equals to Zero.
    So this must be Zero in order to differentiate between the start condition and the Data Size
*/
#define BCM_START_CONDITION     (0x00)  

/*
|-----------------------------------------------------------------------------------------------------------|
|                                   Buffer over BCM Format                                                  |
|-----------------------------------------------------------------------------------------------------------|
|   Start Condition [0x00]  |   Send/Receive Data Length (Little Endian)    |   Data To Send/Receive Bytes  |
|<--------- 1 Byte -------->|<---------- 2 Bytes (Little Endian)----------->|<-------- N Byte(s) ---------->|
|-----------------------------------------------------------------------------------------------------------|
*/

typedef enum
{
    SERIAL_COMM_OVER_UART                   = 0     ,
    SERIAL_COMM_OVER_SPI                            ,
    SERIAL_COMM_OVER_I2C                            ,
    SERIAL_COMM_BUS_TOTAL
}enu_serial_communication_bus_t;

typedef enum
{
    SERIAL_COMM_FULL_DUPLEX                 = 0     ,
    SERIAL_COMM_HALF_DUPLEX                         ,
    SERAIL_COMM_TOTAL
}enu_serial_communication_type_t;

typedef enum
{
    SERIAL_COMM_SEND_SUCCESS                = 0     ,   /* Successful Sending of the Whole Data */ 
    SERIAL_COMM_SEND_FAIL                           ,   /* This means some of the data byte(s) were not sent in the specific timeout */
    SERIAL_COMM_RECEIVE_SUCCESS                     ,   /* Successful Receiving of the Whole Data */
    SERIAL_COMM_RECEIVE_FAIL                        ,   /* This means either that the expected to receive size exceeds the buffer length || The Receiving of data time out*/
    SERIAL_COMM_TOTAL   
}enu_serial_comm_operation_t;

typedef enum
{
    SERIAL_COMM_MEDIUM_STATUS_IDLE          = 0     ,
    SERIAL_COMM_MEDIUM_STATUS_OPERATING             ,
    SERIAL_COMM_MEDIUM_STATUS_BUSY                  ,
    SERIAL_COMM_MEDIUM_STATUS_TOTAL
}enu_serial_comm_status_t;

/**
 * @typedef                                 :   ptr_func_serial_comm_callback_t
 * 
 * @brief                                   :   Declaration of Serial Communication Callback Function
 * 
 * @param[out] enu_serial_comm_operation    :   Type of Operation Done
 * 
 * @param[out] ptr_buffer                   :   Pointer to the Receive Buffer
 *                                              Can be assigned to @value: NULL_PTR in case of @param: enu_serial_comm_operation was reporting a SEND Operation Code
 *                                              The Caller of the BCM or any Serial Communication Protocol has to create a buffer and keep it a live
 *                                              This is achieved by making the buffer static/global or both 
 *                                              OR Allocate a buffer dynamically in the heap and destroy it in the deinit function of the module. 
 * 
 * @param[out] uint16_buffer_length         :   Length of the Received Data.
 * 
 */
typedef void (*ptr_func_serial_comm_callback_t) (enu_serial_comm_operation_t enu_serial_comm_operation, uint8_t_* ptr_buffer, uint16_t_ uint16_buffer_length);

typedef enu_system_status_code_t                (*ptr_func_comm_init_t)                 (enu_serial_communication_bus_t enu_serial_communication_bus, uint8_t_ uint8_channel_num, ptr_func_serial_comm_callback_t ptr_func_serial_comm_callback, uint8_t_* ptr_uint8_rcv_buff, uint16_t_ uint16_rcv_buff_len);
typedef enu_system_status_code_t                (*ptr_func_comm_deinit_t)               (enu_serial_communication_bus_t enu_serial_communication_bus, uint8_t_ uint8_channel_num);
typedef enu_system_status_code_t                (*ptr_func_comm_send_t)                 (enu_serial_communication_bus_t enu_serial_communication_bus, uint8_t_ uint8_channel_num, uint8_t_ uint8_data);
typedef enu_system_status_code_t                (*ptr_func_comm_send_n_t)               (enu_serial_communication_bus_t enu_serial_communication_bus, uint8_t_ uint8_channel_num, uint8_t_* ptr_uint8_buff, uint16_t_ uint16_buff_len);
typedef enu_system_status_code_t                (*ptr_func_comm_get_medium_status_t)    (enu_serial_communication_bus_t enu_serial_communication_bus, enu_serial_comm_status_t* ptr_enu_serial_comm_status);

typedef struct
{
    ptr_func_comm_init_t                        ptr_func_comm_init;                 /* Pointer to the Initialization Function of the Medium */
    ptr_func_comm_deinit_t                      ptr_func_comm_deinit;               /* Pointer to the Deinitialization Function of the Medium */
    ptr_func_comm_send_t                        ptr_func_comm_send;                 /* Pointer to the Send Function of a Single Byte */
    ptr_func_comm_send_n_t                      ptr_func_comm_send_n;               /* Pointer to the Send Function of a Buffer of Data Bytes */
    ptr_func_comm_get_medium_status_t           ptr_func_comm_get_medium_status;    /* Pointer to the Medium Status Function. This shall be saved into the BCM Data Base */
}str_serial_medium_helpers_t;

typedef struct
{
    enu_serial_communication_bus_t              enu_serial_communication_bus;       /* The Source File of the BCM Shall track whether the medium is idle or not. Whether by Array of Booleans or calling an API on each Serial Communication Driver */
    uint8_t_                                    uint8_reserved;                     /* Reserved For Future Development. Currently for Structure Padding */
    uint16_t_                                   uint16_rcv_buff_len;                /* Length of the Actual Data Received */
    uint16_t_                                   uint16_max_rcv_buff_len;            /* Maximum Receive Buffer Length */
    uint16_t_                                   uint16_curr_send_buff_index;        /* Current Index in the Send Buffer */
    uint8_t_*                                   ptr_uint8_rcv_buff;                 /* Pointer on the Receive Buffer */
    str_serial_medium_helpers_t                 str_serial_medium_helpers;          /* Structure that contains all the helper functions needed to be provided by the instance creator. In order to perform the serial communication operations */
}str_bcm_instance_t;

/**
 * @brief                                               :   Function Used to Initialize BCM Instance
 * 
 * @param[in,out]   ptr_str_bcm_instance                :   Pointer to BCM Instance
 * @param[in]       ptr_func_serial_comm_callback       :   Pointer to the Callback Function used to Notify The Application With Events. This will be saved in BCM Data Base 
 * 
 * @return      BCM_STATUS_SUCCESS                      :   In case of Successful Operation     
 *              BCM_STATUS_INVALID_MEDIUM_ID            :   In case of Invalid Medium ID, Ie, Out of Range Medium ID     
 *              BCM_STATUS_MEDIUM_IN_USE                :   In case that the Medium is in use in Medium driver    
 *              BCM_STATUS_INVALID_ARGUMENTS            :   In case of Invalid User Function Pointer || Invalid Pointer to the BCM Instance
 *              BCM_STATUS_INVALID_STATE                :   In case that the Medium is in use in BCM Module    
 */
enu_system_status_code_t    bcm_init            (str_bcm_instance_t* ptr_str_bcm_instance, ptr_func_serial_comm_callback_t ptr_func_serial_comm_callback);

/**
 * @brief                                               :   Function Used to Deinitialize the BCM Instance
 * 
 * @param[in,out] ptr_str_bcm_instance                  :   Pointer to the BCM Instance 
 * 
 * @return      BCM_STATUS_SUCCESS                      :   In case of Successful Operation     
 *              BCM_STATUS_INVALID_MEDIUM_ID            :   In case of Invalid Medium ID, Ie, Out of Range Medium ID       
 *              BCM_STATUS_INVALID_ARGUMENTS            :   In case of invalid Pointer to the BCM Instance
 *              BCM_STATUS_INVALID_STATE                :   In case that the Medium was not used previously || not in use currently in BCM Module 
 */
enu_system_status_code_t    bcm_deinit          (str_bcm_instance_t* ptr_str_bcm_instance);

/**
 * @brief                                               :   Function Used to Send One Byte over the BCM Instance
 * 
 * @param[in,out]   ptr_str_bcm_instance                :   Pointer to the BCM Instance
 * @param[in]       uint8_data_to_send                  :   Byte to be Sent over the BCM Instance
 * 
 * @return      BCM_STATUS_SUCCESS                      :   In case of Successful Operation     
 *              BCM_STATUS_INVALID_MEDIUM_ID            :   In case of Invalid Medium ID, Ie, Out of Range Medium ID                      
 *              BCM_STATUS_INVALID_ARGUMENTS            :   In case of invalid Pointer to the BCM Instance   
 *              BCM_STATUS_INVALID_STATE                :   In case that the Medium was not used previously || not in use currently in BCM Module 
 */
enu_system_status_code_t    bcm_send            (str_bcm_instance_t* ptr_str_bcm_instance, uint8_t_ uint8_data_to_send);

/**
 * @brief                                               :   Function Used to Send Buffer over the BCM Instance
 * 
 * @param[in,out]   ptr_str_bcm_instance                :   Pointer to the BCM Instance 
 * @param[in]       ptr_uint8_buff                      :   Pointer to the Data Buffer
 * @param[in]       uint16_buff_len                     :   Length of the Data Buffer
 * 
 * @return      BCM_STATUS_SUCCESS                      :   In case of Successful Operation     
 *              BCM_STATUS_INVALID_MEDIUM_ID            :   In case of Invalid Medium ID, Ie, Out of Range Medium ID                      
 *              BCM_STATUS_INVALID_ARGUMENTS            :   In case of invalid Pointer to the BCM Instance  
 *              BCM_STATUS_INVALID_STATE                :   In case that the Medium was not used previously || not in use currently in BCM Module 
 */
enu_system_status_code_t    bcm_send_n          (str_bcm_instance_t* ptr_str_bcm_instance, uint8_t_* ptr_uint8_buff, uint16_t_ uint16_buff_len);

/**
 * @brief                                               :   Function Used to Handle the Periodic Operation of the BCM And Take Actions in Sending || Notifying the User With the Operation Result      
 * 
 * @param[in,out]   ptr_str_bcm_instance                :   Pointer to the BCM Instance 
 */
void                        bcm_dispatcher      (str_bcm_instance_t* ptr_str_bcm_instance);

#endif      /*__BCM_H__*/
