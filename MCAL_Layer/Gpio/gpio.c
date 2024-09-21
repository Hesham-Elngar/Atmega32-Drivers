#include "gpio.h"
#include "gpio_private.h"

Return_Status GPIO_Pin_Init(GPIO_Pin_Config* pin)
{
	Return_Status ret = R_NOK;
	if (pin != NULL)
	{
		ret = R_OK;
		GPIO_Set_Pin_Direction(pin, pin->direction);
		GPIO_Set_Pin_Logic(pin, pin->logic);
	}
	return ret;
}

Return_Status GPIO_Set_Pin_Direction(GPIO_Pin_Config* pin, uint8_t direction)
{
	Return_Status ret = R_NOK;
	if (pin != NULL)
	{
		ret = R_OK;
		volatile uint8_t* reg;
		switch (pin->port)
		{
			case PORTA:  reg = &PDDRA; break;
			case PORTB:  reg = &PDDRB; break;
			case PORTC:  reg = &PDDRC; break;
			case PORTD:  reg = &PDDRD; break;
		}
		switch (direction)
		{
			case GPIO_DIRECTION_INPUT:  CLR_BIT(*reg, pin->pin); break;
			case GPIO_DIRECTION_OUTPUT: SET_BIT(*reg, pin->pin); break;
		}
	}
	return ret;
}

Return_Status GPIO_Get_Pin_Direction(GPIO_Pin_Config* pin, uint8_t* direction)
{
	Return_Status ret = R_NOK;
	if (pin != NULL)
	{
		ret = R_OK;
		switch (pin->port)
		{
			case PORTA: *direction = READ_BIT(PDDRA, pin->pin); break;
			case PORTB: *direction = READ_BIT(PDDRB, pin->pin); break;
			case PORTC: *direction = READ_BIT(PDDRC, pin->pin); break;
			case PORTD: *direction = READ_BIT(PDDRD, pin->pin); break;
		}
	}
	return ret;
}

Return_Status GPIO_Set_Pin_Logic(GPIO_Pin_Config* pin, uint8_t logic)
{
	Return_Status ret = R_NOK;
	if (pin != NULL)
	{
		ret = R_OK;
		volatile uint8_t* reg;
		switch (pin->port)
		{
			case PORTA:  reg = &PPORTA; break;
			case PORTB:  reg = &PPORTB; break;
			case PORTC:  reg = &PPORTC; break;
			case PORTD:  reg = &PPORTD; break;
		}
		switch (logic)
		{
			case GPIO_LOGIC_LOW:  CLR_BIT(*reg, pin->pin); break;
			case GPIO_LOGIC_HIGH: SET_BIT(*reg, pin->pin); break;
		}
	}
	return ret;
}

Return_Status GPIO_Get_Pin_Logic(GPIO_Pin_Config* pin, uint8_t* logic)
{
	Return_Status ret = R_NOK;
	if (pin != NULL)
	{
		ret = R_OK;
		switch (pin->port)
		{
			case PORTA: *logic = READ_BIT(PPORTA, pin->pin); break;
			case PORTB: *logic = READ_BIT(PPORTB, pin->pin); break;
			case PORTC: *logic = READ_BIT(PPORTC, pin->pin); break;
			case PORTD: *logic = READ_BIT(PPORTD, pin->pin); break;
		}
	}
	return ret;
}

Return_Status GPIO_Active_Pin_PullUp_Resistor(GPIO_Pin_Config* pin)
{
	Return_Status ret = R_NOK;
	if (pin != NULL)
	{
		ret = R_OK;
		switch (pin->port)
		{
			case PORTA: CLR_BIT(PDDRA, pin->pin); SET_BIT(PPORTA, pin->pin); break;
			case PORTB: CLR_BIT(PDDRB, pin->pin); SET_BIT(PPORTB, pin->pin); break;
			case PORTC: CLR_BIT(PDDRC, pin->pin); SET_BIT(PPORTC, pin->pin); break;
			case PORTD: CLR_BIT(PDDRD, pin->pin); SET_BIT(PPORTD, pin->pin); break;
		}
	}
	return ret;
}

Return_Status GPIO_DeActive_Pin_PullUp_Resistor(GPIO_Pin_Config* pin)
{
	Return_Status ret = R_NOK;
	if (pin != NULL)
	{
		ret = R_OK;
		switch (pin->port)
		{
			case PORTA: CLR_BIT(PDDRA, pin->pin); CLR_BIT(PPORTA, pin->pin); break;
			case PORTB: CLR_BIT(PDDRB, pin->pin); CLR_BIT(PPORTB, pin->pin); break;
			case PORTC: CLR_BIT(PDDRC, pin->pin); CLR_BIT(PPORTC, pin->pin); break;
			case PORTD: CLR_BIT(PDDRD, pin->pin); CLR_BIT(PPORTD, pin->pin); break;
		}
	}
	return ret;
}

Return_Status GPIO_Toggle_Pin(GPIO_Pin_Config* pin)
{
	Return_Status ret = R_NOK;
	if (pin != NULL)
	{
		ret = R_OK;
		switch (pin->port)
		{
			case PORTA: TOGGLE_BIT(PPORTA, pin->pin); break;
			case PORTB: TOGGLE_BIT(PPORTB, pin->pin); break;
			case PORTC: TOGGLE_BIT(PPORTC, pin->pin); break;
			case PORTD: TOGGLE_BIT(PPORTD, pin->pin); break;
		}
	}
	return ret;
}

/**************************************************************/

Return_Status GPIO_Set_Port_Direction(uint8_t port, uint8_t direction)
{
	switch (direction)
	{
		case GPIO_DIRECTION_INPUT:  direction = 0x00; break;
		case GPIO_DIRECTION_OUTPUT: direction = 0xFF; break;
	}
	switch (port)
	{
		case PORTA: PDDRA = direction; return R_OK;
		case PORTB: PDDRB = direction; return R_OK;
		case PORTC: PDDRC = direction; return R_OK;
		case PORTD: PDDRD = direction; return R_OK;
	}
	return R_NOK;
}

Return_Status GPIO_Get_Port_Direction(uint8_t port, uint8_t* direction)
{
	switch (port)
	{
		case PORTA: *direction = PDDRA; return R_OK;
		case PORTB: *direction = PDDRB; return R_OK;
		case PORTC: *direction = PDDRC; return R_OK;
		case PORTD: *direction = PDDRD; return R_OK;
	}
	return R_NOK;
}

Return_Status GPIO_Set_Port_Logic(uint8_t port, uint8_t logic)
{
	switch (logic)
	{
		case GPIO_LOGIC_LOW:  logic = 0x00; break;
		case GPIO_LOGIC_HIGH: logic = 0xFF; break;
	}
	switch (port)
	{
		case PORTA: PPORTA = logic; return R_OK;
		case PORTB: PPORTB = logic; return R_OK;
		case PORTC: PPORTC = logic; return R_OK;
		case PORTD: PPORTD = logic; return R_OK;
	}
	return R_NOK;
}

Return_Status GPIO_Get_Port_Logic(uint8_t port, uint8_t* logic)
{
	switch (port)
	{
		case PORTA: *logic = PPORTA; return R_OK;
		case PORTB: *logic = PPORTB; return R_OK;
		case PORTC: *logic = PPORTC; return R_OK;
		case PORTD: *logic = PPORTD; return R_OK;
	}
	return R_NOK;
}

Return_Status GPIO_Active_Port_PullUp_Resistor(uint8_t port)
{
	switch (port)
	{
		case PORTA: PDDRA = 0x00; PPORTA = 0xFF; return R_OK;
		case PORTB: PDDRB = 0x00; PPORTB = 0xFF; return R_OK;
		case PORTC: PDDRC = 0x00; PPORTC = 0xFF; return R_OK;
		case PORTD: PDDRD = 0x00; PPORTD = 0xFF; return R_OK;
	}
	return R_NOK;
}

Return_Status GPIO_DeActive_Port_PullUp_Resistor(uint8_t port)
{
	switch (port)
	{
		case PORTA: PDDRA = 0x00; PPORTA = 0x00; return R_OK;
		case PORTB: PDDRB = 0x00; PPORTB = 0x00; return R_OK;
		case PORTC: PDDRC = 0x00; PPORTC = 0x00; return R_OK;
		case PORTD: PDDRD = 0x00; PPORTD = 0x00; return R_OK;
	}
	return R_NOK;
}

Return_Status GPIO_Toggle_Port(uint8_t port)
{
	switch (port)
	{
		case PORTA: PPORTA ^= 0xFF; return R_OK;
		case PORTB: PPORTB ^= 0xFF; return R_OK;
		case PORTC: PPORTC ^= 0xFF; return R_OK;
		case PORTD: PPORTD ^= 0xFF; return R_OK;
	}
	return R_NOK;
}
