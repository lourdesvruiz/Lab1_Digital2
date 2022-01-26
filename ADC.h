/* 
 * File:  ADC.h 
 * Author: Lourdes Ruiz
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef ADC_H
#define	ADC_H

/*
 * Liberias
 */
#include <xc.h> // include processor files - each processor file is guarded.
#include <stdint.h>


/*
 * Variables 
 */
uint8_t bigger_value;
uint8_t smaller_value;

/*
 * Prototipos de funciones 
 */

char conversion_1(char ADC);
char conversion_2(char ADC);

#endif