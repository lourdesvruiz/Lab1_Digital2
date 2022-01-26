#include <xc.h> // include processor files - each processor file is guarded.
#include <stdint.h>
#include "IOCB_counter.h"

uint8_t antirrebote1 = 0;
uint8_t antirrebote2 = 0;
uint8_t counter_button = 0;

void InterruptOCB(){
    if (RBIF){
        
        //Contador ascendente
        if (PORTBbits.RB0 == 0){
            antirrebote1 = 1;
        }
        if (PORTBbits.RB0 == 1 && antirrebote1 == 1){
            counter_button++;
            antirrebote1 = 0;
        }
        
        //Contador descendente
        if (PORTBbits.RB1 == 0){
            antirrebote2 = 1;
        }
        if (PORTBbits.RB1 == 1 && antirrebote2 == 1){
            counter_button--;
            antirrebote2 = 0;
        }
        RBIF = 0;
        }
}