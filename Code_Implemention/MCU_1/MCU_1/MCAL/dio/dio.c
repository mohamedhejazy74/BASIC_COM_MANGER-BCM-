/*
 * dio.c
 *
 * Created: 4/5/2023 8:04:45 PM
 *  Author:  Mohamed Abdel-Wahab
 */ 
#include "dio.h"
/* Reference to the Data Direction Control Registers */
static volatile uint8_t *ddr_registers[PORT_MAX_NUMBER] = {&DDRA, &DDRB, &DDRC, &DDRD};
/* Reference to the Data PIN Register (Read  Data ) */
static const volatile uint8_t *pin_registers[PORT_MAX_NUMBER]  = {&PINA , &PINB , &PINC , &PIND };
/* Reference to the Port Status Register (Write data)  */
static volatile uint8_t *port_registers[PORT_MAX_NUMBER] = {&PORTA, &PORTB, &PORTC, &PORTD};

Std_ReturnType DIO_pin_direction_intialize(const pin_config_t *pin_config_ptr,direction_t a_direction)
{
	Std_ReturnType ret = E_OK;
	if(NULL == pin_config_ptr || (pin_config_ptr->pin > PORT_PIN_MAX_NUMBER-1) || (pin_config_ptr->port > PORT_MAX_NUMBER-1))
	{
		ret = E_NOT_OK;
	}
	else
	{
		switch(a_direction)
		{
			case DIO_DIRECTION_OUTPUT:
				SET_BIT(*(ddr_registers[pin_config_ptr->port]),pin_config_ptr->pin);
				break;
			case DIO_DIRECTION_INPUT:
				CLEAR_BIT(*(ddr_registers[pin_config_ptr->port]),pin_config_ptr->pin);
				break;
			default:
				ret = E_NOT_OK;
				break;				
		}
	}
	return ret;
}

Std_ReturnType DIO_pin_write_logic(const pin_config_t *pin_config_ptr, const logic_t a_logic)
{
	Std_ReturnType ret = E_OK;
	if(NULL == pin_config_ptr || (pin_config_ptr->pin > PORT_PIN_MAX_NUMBER-1) || (pin_config_ptr->port > PORT_MAX_NUMBER-1))
	{
		ret = E_NOT_OK;
	}
	else
	{
		switch(a_logic)
		{
			case DIO_LOGIC_LOW:
				CLEAR_BIT(*(port_registers[pin_config_ptr->port]),pin_config_ptr->pin);
				break;
			case DIO_LOGIC_HIGH:
				SET_BIT(*(port_registers[pin_config_ptr->port]),pin_config_ptr->pin);
				break;
			default:
				ret = E_NOT_OK;
				break;
		}
	}
	return ret;
}

Std_ReturnType DIO_pin_read_logic(const pin_config_t * pin_config_ptr, logic_t *logic_ptr)
{
	Std_ReturnType ret = E_OK;
	if(NULL == pin_config_ptr || NULL == logic_ptr || (pin_config_ptr->pin > PORT_PIN_MAX_NUMBER-1) || (pin_config_ptr->port > PORT_MAX_NUMBER-1))
	{
		ret = E_NOT_OK;
	}
	else
	{
		*logic_ptr = READ_BIT(*(pin_registers[pin_config_ptr->port]),pin_config_ptr->pin);
	}
	return ret;
}

Std_ReturnType DIO_pin_toggle_logic(const pin_config_t *pin_config_ptr)
{
	Std_ReturnType ret = E_OK;
	if(NULL == pin_config_ptr || (pin_config_ptr->pin > PORT_PIN_MAX_NUMBER-1) || (pin_config_ptr->port > PORT_MAX_NUMBER-1))
	{
		ret = E_NOT_OK;
	}
	else
	{
		 TOGGLE_BIT(*(port_registers[pin_config_ptr->port]),pin_config_ptr->pin);
	}
	return ret;
}

/*Std_ReturnType DIO_pin_intialize(const pin_config_t *pin_config_ptr)
{
	Std_ReturnType ret = E_OK;
	if(NULL == pin_config_ptr || (pin_config_ptr->pin > PORT_PIN_MAX_NUMBER-1) || (pin_config_ptr->port > PORT_MAX_NUMBER-1))
	{
		ret = E_NOT_OK;
	}
	else
	{
		ret	|= DIO_pin_direction_intialize(pin_config_ptr);
		ret	|= DIO_pin_write_logic(pin_config_ptr,pin_config_ptr->logic);
	}
	return ret;
}
*/
Std_ReturnType DIO_port_direction_intialize(const port_index_t a_port_index, uint8_t a_direction)
{
	Std_ReturnType ret = E_OK;
	if( (a_port_index > PORT_PIN_MAX_NUMBER-1))
	{
		ret = E_NOT_OK;
	}
	else
	{
		*(ddr_registers[a_port_index]) = a_direction;
	}
	return ret;
}
Std_ReturnType DIO_port_write_logic(const port_index_t a_port_index , uint8_t a_logic)
{
	Std_ReturnType ret = E_OK;
	if( (a_port_index > PORT_PIN_MAX_NUMBER-1))
	{
		ret = E_NOT_OK;
	}
	else
	{
		*(port_registers[a_port_index]) = a_logic;
	}
	return ret;
}
Std_ReturnType DIO_port_read_logic(const port_index_t a_port_index , uint8_t *const a_logic_ptr)
{
	Std_ReturnType ret = E_OK;
	if( (a_port_index > PORT_PIN_MAX_NUMBER-1))
	{
		ret = E_NOT_OK;
	}
	else
	{
		*a_logic_ptr = *(pin_registers[a_port_index]);
	}
	return ret;
}
Std_ReturnType DIO_port_toggle_logic(const port_index_t a_port_index)
{
	Std_ReturnType ret = E_OK;
	if( (a_port_index > PORT_PIN_MAX_NUMBER-1))
	{
		ret = E_NOT_OK;
	}
	else
	{
		*(port_registers[a_port_index]) ^= U8_BIT_REG_MASK;
	}
	return ret;
}