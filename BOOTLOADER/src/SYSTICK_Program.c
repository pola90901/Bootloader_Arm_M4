/*
 * SYSTICK_Program.c
 *
 *  Created on: Jan 29, 2023
 *      Author: abdelrahmanhossam
 */



#include "../include/LIB/types.h"
#include "../include/LIB/util.h"
#include "../include/LIB/LIB.h"



#include "../include/MCAL/SYSTICK/SYSTIC_Interface.h"
#include "../include/MCAL/SYSTICK/SYSTIC_Private.h"
#include "../include/MCAL/SYSTICK/SYSTIC_Cfg.h"

static u32 OVFs_Number=0;
static u32 rem = 0;
static u8 ModeOfInterval = STOP_INTERVAL;
static void (*SYSTICK_Callback)(void)=NULL;
void MSYSTICK_voidConfig (void)
{
	// Configuration for the INT
	#if (SYSTICK_TICKINT == ENABLE)
		SET_BIT(STK->CTRL,1);
	#elif (SYSTICK_TICKINT == DISABLE)
		CLR_BIT(STK->CTRL,1);
	#else
		#error "Wrong INTERRUPT Configuration"
	#endif

	// Configuration for the CLK
	#if (SYSTICK_CLOCK == CLK_AHB_8)
		CLR_BIT(STK->CTRL,2);
	#elif (SYSTICK_CLOCK == CLK_AHB)
		SET_BIT(STK->CTRL,2);
	#else
		#error "Wrong CLOCK Configuration"
	#endif
}

 void MSYSTICK_voidEnable(void)
{
	SET_BIT(STK->CTRL,0);
}

 void MSYSTICK_voidDisable(void)
{
	CLR_BIT(STK->CTRL,0);
}

inline void MSYSTICK_voidSetPreload (u32 A_u32Preload)
{
	STK->LOAD = A_u32Preload;
	STK->VAL  = 0;
}

static void  setBusyWait (u32 A_u32Ticks)
{
	MSYSTICK_voidSetPreload (A_u32Ticks);
	MSYSTICK_voidEnable();
	while (GET_BIT(STK->CTRL,16)==0);
	MSYSTICK_voidDisable();
	MSYSTICK_voidSetPreload(0);
}

void MSYSTICK_voidSetBusyWait (u32 A_u32Time, TimeType A_u8TickType)
{
	f32 local_f32TickTime=0.0;
	#if (SYSTICK_CLOCK == CLK_AHB_8)
		local_f32TickTime = (f32)1 / ((f32)CLOCK_MHZ / (f32)8);
	#elif (SYSTICK_CLOCK == CLK_AHB)
		local_f32TickTime = (f32)1 / (f32)CLOCK_MHZ;
	#else
		#error "Wrong CLOCK Configuration"
	#endif

	u32 local_u32NoOfTicks = A_u32Time / local_f32TickTime;

	switch (A_u8TickType)
	{
	case MICRO_SEC: break;
	case MILLI_SEC: local_u32NoOfTicks *= 1000UL; break;
	case SEC: local_u32NoOfTicks *= 1000000UL; break;
	default: break;
	}

	if (local_u32NoOfTicks < 16777216)
	{
		setBusyWait (local_u32NoOfTicks);
	}
	else if (local_u32NoOfTicks > 16777216)
	{
		while (local_u32NoOfTicks > 0)
		{
			if (local_u32NoOfTicks > 16777216)
			{
				setBusyWait (16777215);
				local_u32NoOfTicks -= 16777216;
			}
			else
			{
				setBusyWait (local_u32NoOfTicks);
				local_u32NoOfTicks = 0;
			}
		}
	}

}

void MSYSTICK_voidSetIntervalSingle (u32 A_u32Time, u8 A_u8TickType, void (*A_ptrToFunc)(void))
{
	f32 local_f32TickTime=0.0;
		#if (SYSTICK_CLOCK == CLK_AHB_8)
		local_f32TickTime = (f32)1 / ((f32)CLOCK_MHZ / (f32)8);
		#elif (SYSTICK_CLOCK == CLK_AHB)
		local_f32TickTime = (f32)1 / (f32)CLOCK_MHZ;
		#else
			#error "Wrong CLOCK Configuration"
		#endif

		u32 local_u32NoOfTicks = A_u32Time / local_f32TickTime;

		switch (A_u8TickType)
		{
		case MICRO_SEC: break;
		case MILLI_SEC: local_u32NoOfTicks *= 1000UL; break;
		case SEC: local_u32NoOfTicks *= 1000000UL; break;
		default: break;
		}

		ModeOfInterval = SINGLE_INTERVAL;
		if (local_u32NoOfTicks < 16777216)
		{
			OVFs_Number = 1;
			rem=0;
			MSYSTICK_voidSetPreload (local_u32NoOfTicks);
		}
		else
		{
			OVFs_Number = local_u32NoOfTicks / 16777216;
			rem = local_u32NoOfTicks % 16777216;
			MSYSTICK_voidSetPreload (16777215);
		}

		if (A_ptrToFunc != NULL)
		{
		 MSYSTICK_voidEnable();
		 SYSTICK_Callback = A_ptrToFunc;
		 SET_BIT(STK->CTRL,1); // Enable INT
		}
}

void MSYSTICK_voidSetIntervalPeriodic (u32 A_u32Time, u8 A_u8TickType, void (*A_ptrToFunc)(void))
{
	f32 local_f32TickTime=0.0;
	#if (SYSTICK_CLOCK == CLK_AHB_8)
	local_f32TickTime = (f32)1 / ((f32)CLOCK_MHZ / (f32)8);
	#elif (SYSTICK_CLOCK == CLK_AHB)
	local_f32TickTime = (f32)1 / (f32)CLOCK_MHZ;
	#else
		#error "Wrong CLOCK Configuration"
	#endif

	u32 local_u32NoOfTicks = A_u32Time / local_f32TickTime;

	switch (A_u8TickType)
	{
	case MICRO_SEC: break;
	case MILLI_SEC: local_u32NoOfTicks *= 1000UL; break;
	case SEC: local_u32NoOfTicks *= 1000000UL; break;
	default: break;
	}

	ModeOfInterval = PERIODIC_INTERVAL;
	if (local_u32NoOfTicks < 16777216)
	{
		OVFs_Number = 1;
		rem=0;
		MSYSTICK_voidSetPreload (local_u32NoOfTicks);
	}
	else
	{
		OVFs_Number = local_u32NoOfTicks / 16777216;
		rem = local_u32NoOfTicks % 16777216;
		MSYSTICK_voidSetPreload (16777215);
	}

	if (A_ptrToFunc != NULL)
	{
	 MSYSTICK_voidEnable();
	 SYSTICK_Callback = A_ptrToFunc;
	 SET_BIT(STK->CTRL,1); // Enable INT
	}
}

void MSYSTICK_voidStopInterval(void)
{
	MSYSTICK_voidDisable();
	CLR_BIT(STK->CTRL,1); // Disable INT
	MSYSTICK_voidSetPreload(0);
}

u32 MSYSTICK_u32GetElapsedTime (void)
{
	u32 local_u32ElapsedTime = 0 ;
	local_u32ElapsedTime = ((STK->LOAD)-(STK->VAL));
	return local_u32ElapsedTime;
}

u32 MSYSTIC_u32GetRemainingTime (void)
{
	u32 local_u32RemainingTime=0;
	local_u32RemainingTime = (STK->VAL);
	return local_u32RemainingTime;
}


void SysTick_Handler (void)
{
	u8 local_u8Flag=0;
	static u32 counter;
	counter++;
	if (counter >= OVFs_Number)
	{
		if (rem==0)
		{
			counter=0;
			if (ModeOfInterval == SINGLE_INTERVAL)
			{
				MSYSTICK_voidStopInterval();
			}
			if (SYSTICK_Callback != NULL)
			{
				SYSTICK_Callback();
			}
		}
		else
		{
			MSYSTICK_voidSetPreload (rem);
			rem=0;
		}
	}
	local_u8Flag = GET_BIT(STK->CTRL,16); // Clear INT Flag
}
