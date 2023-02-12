#include "../include/LIB/types.h"
#include "../include/LIB/util.h"
#include "../include/MCAL/FPEC/FPEC_interface.h"
#include "../include/MCAL/FPEC/FPEC_private.h"
#include "../include/MCAL/FPEC/FPEC_config.h"


void FPEC_voidEraseAppArea(void)
{
	u8 i;
	
	for (i=1;i<5;i++)					// ERASE after 16K byte tell 256k
	{
		FPEC_voidFlashSectorErase(i);
	}
}

void FPEC_voidFlashSectorErase(u8 Copy_u8SectoreNumber)
{
	/* Wait Busy Flag */
	while (GET_BIT(FPEC->SR,16) == 1); 				// modified

	/* Check if FPEC is locked or not */
	if ( GET_BIT(FPEC->CR,31) == 1)				// modified
	{
		FPEC -> KEYR = 0x45670123;      // the same
		FPEC -> KEYR = 0xCDEF89AB;		// the same
	}
	
	/* Page Erase Operation */
	SET_BIT(FPEC->CR,1);			// will ERASE SECTOR not page in M4 (SER)

	/* Write Page address */
	//FPEC->AR = (u32)(Copy_u8PageNumber * 1024) + 0x08000000 ; // postponed

	// Write Sector number to erase
	FPEC->CR|=Copy_u8SectoreNumber <<3;

	/* Start operation */
	SET_BIT(FPEC->CR,16); // modified

	/* Wait Busy Flag */
	while (GET_BIT(FPEC->SR,16) == 1);// modified

	/* EOP */
	SET_BIT(FPEC->SR,0);	// modified
	CLR_BIT(FPEC->CR,1);	// same
}

void FPEC_voidFlashWrite(u32 Copy_u32Address, u16* Copy_u16Data, u8 Copy_u8Length)
{
	u8 i;
	volatile u16 Temp;

	while (GET_BIT(FPEC->SR,16) == 1);// modified

	/* Check if FPEC is locked or not */
	if ( GET_BIT(FPEC->CR,31) == 1 )// modified
	{
		FPEC -> KEYR = 0x45670123;  // the same
		FPEC -> KEYR = 0xCDEF89AB;	// the same
	}
	
	
	for (i = 0; i< Copy_u8Length; i++)
	{
		/* Write Flash Programming */
		SET_BIT(FPEC->CR,0);		//the same


		FPEC->CR|=1<<8; // Parrallism (Psize) -> x16 	2 Byte Half word
		/* Half word operation */
		Temp = Copy_u16Data[i];
		*((volatile u16*)Copy_u32Address) = Copy_u16Data[i];
		Copy_u32Address += 2 ;

		/* Wait Busy Flag */
		while (GET_BIT(FPEC->SR,16) == 1);
	
		/* EOP */
		SET_BIT(FPEC->SR,0);
		CLR_BIT(FPEC->CR,1);
	}

}
