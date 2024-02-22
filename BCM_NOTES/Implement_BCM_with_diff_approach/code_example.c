enu_state_t bcm_init(str_bcm_instance_t* ptr_str_bcm_instance)
{
    enu_state_t enu_state_retval = SUCCESS;
    if((ptr_str_bcm_instance != NULL) && (ptr_str_bcm_instance->init_helper != NULL) && (ptr_str_bcm_instance->channel_id < TOTAL_CHANNELS))
    {
       enu_state_retval = ptr_str_bcm_instance->init_helper(ptr_str_bcm_instance->channel_id);
    }
    else
    {
        enu_state_retval = STATUS_INVALID_ARGS;
    }

    return enu_state_retval;
}

/*bcm.h*/
typedef void (*tpf_callback) (enu_operation_status_t enu_operation_status);

/*App.c*/
static uint8_t_ guint8_send_done = 0;

static void send_done(enu_operation_status_t enu_operation_status)
{
    if(enu_operation_status == SEND_SUCCESS)
    {
        guint8_send_done = 1;   /*Success*/

        toggle_led(LED_0);
    }
    else
    {
        guint8_send_done = 2;   /*Send Failure*/
    }
}

int main (void)
{
    enu_state_t enu_state_retval = SUCCESS;

    enu_state_retval = bcm_register_callback(TX_DONE, send_done);

    enu_state_retval = bcm_send_n(au8_data, sizeof(au8_data));
    while(1)
    {
        if(guint8_send_done == 1)
        {
            guint8_send_done = 0;

            /*Send Success*/
            
        }
        else if(guint8_send_done == 2)
        {
            guint8_send_done = 0;

            /*Disconnect*/
        }

    }
}

/*bcm.c*/
enu_state_t bcm_register_callback(enu_operation_t enu_operation, tpf_callback pf_callback)
{
    enu_state_t enu_state_retval = SUCCESS;

    if((enu_operation < TOTAL_OPERATIONS) && (pf_callback != NULL))
    {
        gapf_callbacks[enu_operation] = pf_callback;
    }   
    else
    {
        enu_state_retval = INVALID_ARGUMENTS;
    }

    return enu_state_retval;
}

void bcm_uart_cbk(enu_uart_operation_t enu_uart_operation)
{
    switch(enu_uart_operation)
    {
        case UART_TX_DONE:
        {
            gapf_callbacks[TX_DONE](SEND_SUCCESS);
            break;
        }
        case UART_RX_DONE:
        {
            gapf_callbacks[RX_DONE](SEND_SUCCESS);
            break;
        }
        default:
        {
            break;
        }
    }
}

/*uart.c*/
ISR(UART_TX_DONE)
{
    static uint16_counter = 0;
    uint16_counter++;

    if((guint16_data_length == uint16_counter) && (uint16_counter != 0))
    {
        uint16_counter = 0;
        gapf_callbacks[guint8_channel_id](UART_TX_DONE);
    }

    else
    {
        UDR = gpu8_data[uint16_counter];
    }
}


