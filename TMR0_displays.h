/* 
 * File: TMR0_displays.h
 * Author: Lourdes Ruiz
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef TMR0_displays_H
#define	TMR0_displays_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>



/*
 * Variables 
 */

char disps;
uint8_t bigger_value;
uint8_t smaller_value;
unsigned char displays[];

/*
 * Prototipos de funciones 
 */

void InterruptTMR0(uint8_t bigger_value, uint8_t smaller_value);

#endif	/* XC_HEADER_TEMPLATE_H */



