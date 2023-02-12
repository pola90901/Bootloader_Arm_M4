#ifndef FPEC_PRIVATE
#define FPEC_PRIVATE
/*
typedef union
{
	struct{
		u32  PG    :1 ;
		u32  PER   :1 ;
		u32  MER   :1 ;
		u32  RES1  :1 ;
		u32  OPTPG :1 ;
		u32  OPTER :1 ;
		u32  STRT  :1 ;
		u32  LOCK  :1 ;
		u32  RES2  :1 ;
		u32  OPTWRE:1 ;
		u32  ERRIE :1 ;
		u32  RES3  :1 ;
		u32  EOPIE :1 ;
		u32  RES4  :19;
	}BitAccess;
	
	u32 WordAccess;
}FPEC_CR_TYPE;
*/
//#define FPEC_CR ((FPEC_CR_TYPE*)0x40023C10)

typedef struct
{
	volatile u32 ACR;			// found but not used
	volatile u32 KEYR;			/* USED*/
	volatile u32 OPTKEYR;		//found but  not used
	volatile u32 SR;			/* USED*/
	volatile u32 CR;			/* USED*/
	volatile u32 OPTCR;    // new for M401
	//volatile u32 AR; 	   // used but not found in M4

}FPEC_TYPE;

#define FPEC ((FPEC_TYPE*)0x40023C00)



#endif
