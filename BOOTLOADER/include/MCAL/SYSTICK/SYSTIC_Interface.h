/*
 * SYSTIC_Interface.h
 *
 *  Created on: Jan 29, 2023
 *      Author: abdelrahmanhossam
 */

#ifndef SYSTIC_INTERFACE_H_
#define SYSTIC_INTERFACE_H_

#define ENABLE  1
#define DISABLE 0

#define CLK_AHB   0
#define CLK_AHB_8 1

typedef enum{
	MICRO_SEC=0,
	MILLI_SEC,
	SEC
}TimeType;

typedef enum{
	SINGLE_INTERVAL=0,
	PERIODIC_INTERVAL,
	STOP_INTERVAL
}IntervalType;


void MSYSTICK_voidConfig (void);
void MSYSTICK_voidSetBusyWait (u32 A_u32Time, TimeType A_u8TickType);
void MSYSTICK_voidSetIntervalSingle (u32 A_u32Time, u8 A_u8TickType, void (*A_ptrToFunc)(void));
void MSYSTICK_voidStopInterval(void);
void MSYSTICK_voidEnable(void);
#endif /* SYSTIC_INTERFACE_H_ */
