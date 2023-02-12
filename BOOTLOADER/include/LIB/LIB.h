/*   AUTHOR      : Abdelrahman Hossam               */
/*   Description : LIB		                        */
/*   DATE        : 22 JUL 2020                      */
/*   VERSION     : V01                              */
/****************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LIB_H
#define __LIB_H
#include "../../include/LIB/types.h"






#define VALIDATE(__condition, __msg)                                                \
    do                                  \
    {                                   \
        if (!(__condition))             \
        {                               \
    __asm__ __volatile__(" BKPT #0x1 \n"); /* Stop at software break point */     \
    do                                                                            \
    {                                                                             \
    } while (1); /* Halt on endless loop */                                       \
    }                                   \
    }                                   \
    while (0)

#define NULL  (void * )0

//#define NULL 0
#endif /* __LIB_H */
