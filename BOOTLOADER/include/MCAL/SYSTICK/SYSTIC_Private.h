/*
 * SYSTIC_Private.h
 *
 *  Created on: Jan 29, 2023
 *      Author: abdelrahmanhossam
 */

#ifndef SYSTIC_PRIVATE_H_
#define SYSTIC_PRIVATE_H_

#define STK ((volatile STK_t*) 0xE000E010)

typedef struct
{
	/*SysTick control and status register (STK_CTRL)*/
	volatile u32 CTRL;
	/*SysTick reload value register (STK_LOAD)*/
	volatile u32 LOAD;
	/*SysTick current value register (STK_VAL)*/
	volatile u32 VAL;
	/*SysTick calibration value register (STK_CALIB)*/
	volatile u32 CALIB;
}STK_t;


#endif /* SYSTIC_PRIVATE_H_ */
