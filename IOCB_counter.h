/* 
 * File:  IOCB_counter.h  
 * Author: Lourdes Ruiz
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef IOCB_counter_H
#define	IOCB_counter_H

#include <xc.h> // include processor files - each processor file is guarded. 
#include <stdint.h>

/*
 * Variables 
 */
uint8_t antirrebote1;
uint8_t antirrebote2;


/*
 * Prototipos de funciones 
 */

void InterruptOCB();
#endif	/* XC_HEADER_TEMPLATE_H */

