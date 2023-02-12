/*
 * RCC_Private.h
 *
 *  Created on: Dec 25, 2022
 *      Author: mohan
 */

#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_

/*	Register Definitions	*/

/*
#define GPIOH  ((volatile GPIO_t *)0x40021C00)	//not used in our kit
#define GPIOE  ((volatile GPIO_t *)0x40021000)	//not used in our kit
#define GPIOD  ((volatile GPIO_t *)0x40020C00)	//not used in our kit
*/
#define GPIOC  ((volatile GPIO_t *)0x40020800)
#define GPIOB  ((volatile GPIO_t *)0x40020400)
#define GPIOA  ((volatile GPIO_t *)0x40020000)

typedef struct {

	volatile u32 MODER;
	volatile u32 OTYPER;
	volatile u32 OSPEEDR;
	volatile u32 PUPDR;
	volatile u32 IDR;
	volatile u32 ODR;
	volatile u32 BSRR;
	volatile u32 LCKR;
	volatile u32 AFRL;
	volatile u32 AFRH;

}GPIO_t;



#endif /* GPIO_PRIVATE_H_ */
