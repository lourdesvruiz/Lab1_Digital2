#include <xc.h> // include processor files - each processor file is guarded.
#include <stdint.h>
#include "TMR0_displays.h"

uint8_t disps = 0;

//Array para "tabla" de displays
unsigned char displays[16] =
{
    0b00111111,   
    0b00000110,   
    0b01011011,   
    0b01001111,   
    0b01100110,   
    0b01101101,   
    0b01111101,   
    0b00000111,  
    0b01111111,   
    0b01101111,
    0b01110111,
    0b01111100,
    0b00111001,
    0b01011110,
    0b01111001,
    0b01110001
};

//Esta función nos devuelve dos valores 
void InterruptTMR0(uint8_t bigger_value, uint8_t smaller_value){
    if(T0IF){ 
        TMR0 = 60;  
        switch(disps) {
            case 0:
                PORTC = 0;
                PORTD = displays[bigger_value];   //se muestra en el segundo display el valor más alto (se podría decir que son las decenas si fuera decimal)
                PORTCbits.RC0 = 1;    //se settea el pin del transistor
                disps++;              //se aumenta la variable que controla el case 
                break;
            case 1:
                PORTC = 0;
                PORTD = displays[smaller_value];  //unidades si fuera en decimal
                PORTCbits.RC1 = 1;
                disps = 0;          //se pone en 0 pues solo se usaron dos displays
                break;
              
        }  
        
        
        T0IF = 0;    
    }
}


