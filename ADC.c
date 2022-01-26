#include "ADC.h"
#include <xc.h> // include processor files - each processor file is guarded.
#include <stdint.h>
//Funciones para contador hexadecimal
char conversion_1(char ADC){
        bigger_value = ADC % 16; //el operador mod nos da como resultado el residuo de la division
        return bigger_value;
    }

char conversion_2(char ADC){
        smaller_value = (ADC/16) % 16;  //aca se divide primero dentro de 16 para obtener el número más significativo
        return smaller_value;
    }


//Ejemplo de los cálculos
//101 base 10 a hexadecimal (base 16)
/*
 * Se divide sucesivamente dentro de 16 hasta que el cocientes sea 0.
 * 101/16 = 6, resto 5
 * 6/16 = 0, resto 6
 * Resultado = 65
 */