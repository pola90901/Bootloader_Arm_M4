
#include "../include/LIB/types.h"
#include "../include/LIB/util.h"

#include "../include/MCAL/RCC/RCC_interface.h"
#include "../include/MCAL/SYSTICK/SYSTIC_Interface.h"
#include "../include/MCAL/GPIO/GPIO_Interface.h"
#include "../include/MCAL/USART/USART_interface.h"
#include "../include/MCAL/FPEC/FPEC_interface.h"


void Parser_voidParseRecord(u8* Copy_u8BufData);

volatile u8  u8RecBuffer[100]   ;
volatile u8  u8RecCounter    = 0;
volatile u8  u8TimeOutFlag   = 0;
volatile u16 u16TimerCounter = 0;
volatile u8  u8BLWriteReq    = 1;

typedef void (*Function_t)(void);
Function_t addr_to_call = 0;

void func(void)
{
#define SCB_VTOR   *((volatile u32*)0xE000ED08)

	SCB_VTOR = 0x08004000; /* start address of    for application not bootloader */

	addr_to_call = *(Function_t*)(0x08004004); /* address of reset system in vector table of app */
	addr_to_call();
}


int main()
{
	u8 Local_u8RecStatus;
	MRCC_voidInit();/* __Enable HSI  with 8 MHZ */

	MRCC_voidPeripheralEnable(APB2,USART1);/* ___USART1 */
	MRCC_voidPeripheralEnable(AHB1,GPIOAEN);/* __PortA  */

	MRCC_voidEnable_FPEC();

	MGPIO_SetPinDirection(GPIO_PORTA,GPIO_Pin9,AF_PUSH_PULL,GPIO_MedSpeed);   /*__ TX AFPP */
	MGPIO_SetPinDirection(GPIO_PORTA,GPIO_Pin10,AF_PUSH_PULL,GPIO_MedSpeed);// RX input floating


	MUSART1_voidInit();
	MSYSTICK_voidConfig();
	MSYSTICK_voidEnable();


	MSYSTICK_voidSetIntervalSingle(15,SEC,func);
	while(u8TimeOutFlag == 0)
	{

		Local_u8RecStatus = MUSART1_u8Receive( &(u8RecBuffer[u8RecCounter]) );
		if (Local_u8RecStatus == 1)
		{
			MSYSTICK_voidStopInterval();

			if(u8RecBuffer[u8RecCounter] == '\n')
			{
				if (u8BLWriteReq == 1)
				{
					FPEC_voidEraseAppArea();
					u8BLWriteReq = 0;
				}

				/* Parse */
				Parser_voidParseRecord(u8RecBuffer);
				MUSART1_voidTransmit("ok");
				u8RecCounter = 0;
			}

			else
			{
				u8RecCounter ++ ;
			}

			MSYSTICK_voidSetIntervalSingle(15,SEC,func);
		}

		else
		{

		}
	}

return 0;
}

