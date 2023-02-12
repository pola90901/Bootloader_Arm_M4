/*
 * RCC_Program.c
 *
 *  Created on: Dec 25, 2022
 *      Author: mohan
 */

#include "../include/LIB/types.h"
#include "../include/LIB/util.h"

#include "../include/MCAL/GPIO/GPIO_Interface.h"
#include "../include/MCAL/GPIO/GPIO_Private.h"
#include "../include/MCAL/GPIO/GPIO_Config.h"

static void MGPIO_SetPinSpeed(u8 A_u8PortID,u8 A_u8PinID,u8 A_u8Speed)
{
	switch(A_u8PortID)
	{
	case GPIO_PORTA:
		GPIOA->OSPEEDR &= ~(3<<(2*A_u8PinID));
		GPIOA->OSPEEDR |= (A_u8Speed<<(2*A_u8PinID));
		break;
	case GPIO_PORTB:
		GPIOB->OSPEEDR &= ~(3<<(2*A_u8PinID));
		GPIOB->OSPEEDR |= (A_u8Speed<<(2*A_u8PinID));
		break;
	case GPIO_PORTC:
		GPIOC->OSPEEDR &= ~(3<<(2*A_u8PinID));
		GPIOC->OSPEEDR |= (A_u8Speed<<(2*A_u8PinID));
		break;
	}
}
static void MGPIO_VoidSetPinMode(u8 A_u8PortID,u8 A_u8PinID,u8 A_u8Mode)
{

	switch(A_u8PortID)
	{
	case GPIO_PORTA:  // 0b11 == 3
		GPIOA->MODER &= ~(0b11 << (2*A_u8PinID));
		GPIOA->MODER |=(A_u8Mode << (2*A_u8PinID));
		break;
	case GPIO_PORTB:
		GPIOB->MODER &= ~(0b11 << (2*A_u8PinID));
		GPIOB->MODER |=(A_u8Mode << (2*A_u8PinID));
		break;
	case GPIO_PORTC:
		GPIOC->MODER &= ~(0b11 << (2*A_u8PinID));
		GPIOC->MODER |=(A_u8Mode << (2*A_u8PinID));
		break;
	default: break;
	}
}

static void Static_voidSetPinPullState(u8 A_u8PortID,u8 A_u8PinID,u8 A_u8State)
{switch(A_u8PortID)
{
case GPIO_PORTA:
	GPIOA->PUPDR &= ~(3<<(2*A_u8PinID));
	GPIOA->PUPDR |= (A_u8State<<(2*A_u8PinID));
	break;
case GPIO_PORTB:
	GPIOB->PUPDR &= ~(3<<(2*A_u8PinID));
	GPIOB->PUPDR |= (A_u8State<<(2*A_u8PinID));
	break;
case GPIO_PORTC:
	GPIOC->PUPDR &= ~(3<<(2*A_u8PinID));
	GPIOC->PUPDR |= (A_u8State<<(2*A_u8PinID));
	break;
}
}
static void MGPIO_SetOutPutype(u8 A_u8PortID,u8 A_u8PinID,u8 A_u8Type)
{
	switch (A_u8PortID)
	{
	case GPIO_PORTA: switch (A_u8Type)
	{
	case 0 :CLR_BIT(GPIOA->OTYPER,A_u8PinID);break;
	case 1:SET_BIT(GPIOA->OTYPER,A_u8PinID);	break;
	}
	break;
	case GPIO_PORTB: switch (A_u8Type)
	{
	case 0 :CLR_BIT(GPIOB->OTYPER,A_u8PinID);break;
	case 1:SET_BIT(GPIOB->OTYPER,A_u8PinID);	break;
	}
	break;

	case GPIO_PORTC: switch (A_u8Type)
	{
	case 0 :CLR_BIT(GPIOC->OTYPER,A_u8PinID);break;
	case 1:SET_BIT(GPIOC->OTYPER,A_u8PinID);	break;
	}
	break;
	}
}

void MGPIO_SetPinDirection(u8 A_u8PortID,u8 A_u8PinID,u8 A_u8Direction,u8 copy_u8Speed)
{
	if(A_u8Direction<4)
	{
		MGPIO_VoidSetPinMode(A_u8PortID,A_u8PinID,0);
	}
	else if (A_u8Direction> 4 && A_u8Direction<11)
	{
		MGPIO_VoidSetPinMode(A_u8PortID,A_u8PinID,1);
	}
	else if (A_u8Direction>=11 && A_u8Direction <= 16)
	{
		MGPIO_VoidSetPinMode(A_u8PortID,A_u8PinID,2);
	}
	else if (A_u8Direction == 4)
	{
		MGPIO_VoidSetPinMode(A_u8PortID,A_u8PinID,3);
	}
	switch(A_u8Direction)
	{
	case AF_PUSH_PULL :SEt_AF(A_u8PortID,A_u8PinID,0b0111);break;
	case OUTPUT_PUSH_PULL :
	case OUTPUT_PUSH_PULL_PULL_UP:
	case OUTPUT_PUSH_PULL_PULL_DOWN :
	case AF_PUSH_PULL_PULL_UP :
	case AF_PUSH_PULL_PULL_DOWN :
		MGPIO_SetOutPutype(A_u8PortID,A_u8PinID,0);////////////////////
		break;

	case 	OUTPUT_OPEN_DRAIN :
	case	OUTPUT_PUSH_OPEN_DRAIN_UP :
	case	OUTPUT_PUSH_OPEN_DRAIN_DOWN :
	case	AF_OPEN_DRAIN :
	case 	AF_OPEN_DRAIN_PULL_UP :
	case	AF_OPEN_DRAIN_PULL_DOWN :
		MGPIO_SetOutPutype(A_u8PortID,A_u8PinID,1);
		break;
	}
	switch(A_u8Direction)
	{
	case INPUT_FLOATING:
	case OUTPUT_PUSH_PULL:
	case OUTPUT_OPEN_DRAIN:
	case AF_PUSH_PULL:
	case AF_OPEN_DRAIN:
		Static_voidSetPinPullState(A_u8PortID,A_u8PinID,0);break;
		break;
	case INPUT_PULL_UP:
	case OUTPUT_PUSH_PULL_PULL_UP:
	case OUTPUT_PUSH_OPEN_DRAIN_UP:
	case AF_PUSH_PULL_PULL_UP:
	case AF_OPEN_DRAIN_PULL_UP:
		Static_voidSetPinPullState(A_u8PortID,A_u8PinID,1);break;
		break;
	case INPUT_PULL_DOWN:
	case OUTPUT_PUSH_PULL_PULL_DOWN:
	case OUTPUT_PUSH_OPEN_DRAIN_DOWN:
	case AF_PUSH_PULL_PULL_DOWN:
	case AF_OPEN_DRAIN_PULL_DOWN:
		Static_voidSetPinPullState(A_u8PortID,A_u8PinID,2);break;
		break;
	}

	MGPIO_SetPinSpeed(A_u8PortID,A_u8PinID,copy_u8Speed);
}

void SEt_AF(u8 A_u8PortID,u8 A_u8PinID,u8 A_u8Type){

	switch (A_u8PortID)
		{
		case GPIO_PORTA:

		GPIOA->AFRH|=A_u8Type<<4*(A_u8PinID-8);
			break;
		case GPIO_PORTB:
			GPIOB->AFRH|=A_u8Type<<4*(A_u8PinID-8);
			break;
		case GPIO_PORTC:
			GPIOC->AFRH|=A_u8Type<<4*(A_u8PinID-8);
			break;
		}
}

void MCAL_voidSetPinValue(u8 A_u8PortID,u8 A_u8PinID,u8 copy_u8Value)
{
	switch (A_u8PortID)
	{
	case GPIO_PORTA:
		Assign_Bit(GPIOA->ODR,A_u8PinID,copy_u8Value);
		break;
	case GPIO_PORTB:
		Assign_Bit(GPIOB->ODR,A_u8PinID,copy_u8Value);
		break;
	case GPIO_PORTC:
		Assign_Bit(GPIOC->ODR,A_u8PinID,copy_u8Value);
		break;
	}

}
void MCAL_voidGetPinValue(u8 A_u8PortID,u8 A_u8PinID,u8* copy_u8Value)
{
	switch (A_u8PortID)
	{
	case GPIO_PORTA:
		*copy_u8Value=GET_BIT(GPIOA->IDR,A_u8PinID);
		break;
	case GPIO_PORTB:
		*copy_u8Value=GET_BIT(GPIOB->IDR,A_u8PinID);
		break;
	case GPIO_PORTC:
		*copy_u8Value=GET_BIT(GPIOC->IDR,A_u8PinID);
		break;
	}

}

void AtomicMCAL_voidSetPinValue(u8 A_u8PortID,u8 A_u8PinID,u8 copy_u8Value)
{
	switch(A_u8PortID)
	{
	case GPIO_PORTA:
		if(copy_u8Value ==0)
		{

			GPIOA->BSRR=1<<(A_u8PinID+16);
		}
		else
		{
			GPIOA->BSRR=(1<<A_u8PinID);
		}

		break;
	case GPIO_PORTB:
		if(copy_u8Value ==0)
		{
			GPIOB->BSRR=1<<(A_u8PinID+16);
		}
		else
		{
			GPIOB->BSRR=1<<A_u8PinID;
		}
			break;
	case GPIO_PORTC:
		if(copy_u8Value ==0)
		{
			GPIOC->BSRR=1<<(A_u8PinID+16);
		}
		else
		{
			GPIOC->BSRR=1<<(A_u8PinID+16);
		}

		break;
		}
	}


