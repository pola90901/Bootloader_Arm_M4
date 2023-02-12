/*
 * RCC_interface.h
 *
 *  Created on: Jul 22, 2022
 *      Author: abdelrahmanhossam
 */

#ifndef RCC_INTERFACE_H_
#define RCC_INTERFACE_H_

typedef enum
{
	NOT_RDY =0,
	RDY	   ,
	OUT_OF_RANGE ,
	OK,
	NOK
}Status;

#define HSI	0
#define HSE	1
#define PLL	2

#define ON  1
#define OFF 0

/* System Buses */
#define AHB1 1
#define AHB2 2
#define APB1 3
#define APB2 4

/* AHB1 Peripherals */
#define GPIOAEN 0
#define GPIOBEN 1
#define GPIOCEN 2
#define GPIODEN 3
#define GPIOEEN 4
#define GPIOHEN 7
#define CRCEN	12
#define DMA1EN  21
#define DMA2EN  22

/* AHB2 Peripherals */
#define OTGFSEN 7


/* APB1 Peripherals */
#define TIM2EN   0
#define TIM3EN   1
#define TIM4EN   2
#define TIM5EN   3
#define WWDGEN   11
#define SPI2EN   14
#define SPI3EN   15
#define USART2EN 17
#define I2C1EN   21
#define I2C2EN   22
#define I2C3EN   23
#define PWREN	   28

/* APB2 Peripherals */
#define TIM1   0
#define USART1 4
#define USART6 5
#define ADC1   8
#define SDIO   11
#define SPI1   12
#define SPI4   13
#define SYSCFG 14
#define TIM9   16
#define TIM10  17
#define TIM11  18

void MRCC_voidInit (void);
void MRCC_voidPeripheralEnable(u8 A_u8Bus, u8 A_u8Peripheral);
void MRCC_voidPeripheralDisable(u8 A_u8Bus, u8 A_u8Peripheral);
void MRCC_voidSetClkStatus (const u8 A_u8ClockSource, const u8 A_u8Status);
Status MRCC_StatusIsClkSelected (const u8 A_u8ClkSource);
/* Set input as a system clock */
Status MRCC_StatusSetClkSource (const u8 A_u8ClkSource);
Status MRCC_StatusCheckClkStatus (const u8 A_u8ClkSource);
/* Turn on and off clock source */
void MRCC_voidSetClkStatus (u8 copy_u8ClkSource, u8 copy_u8Status);
/* Set AHB1 and APB1 and APB2 Prescalers */
void MRCC_voidSetBusesPrescaler (u8 A_u8AHB,u8 A_u8APB1,u8 A_u8APB2);
/* Set PLL Factors */
void MRCC_voidSetPLLFactors (u8 copy_u8PLLM, u16 copy_u16PLLN, u8 copy_u8PLLP, u8 copy_u8PLLQ);


void MRCC_voidEnable_FPEC(void);

#endif /* RCC_INTERFACE_H_ */
