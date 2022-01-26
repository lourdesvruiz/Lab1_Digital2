/*
 * File:   interrupts_libraries.c
 * Author: Lourdes Ruiz
 *
 * Created on Jan 24, 2022, 1:52 PM
 * 
 * Descripcion: 
 */


// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <pic16f887.h>

//Se incluyen las librerías hechas por mí 
#include "ADC.h"
#include "TMR0_displays.h"
#include "IOCB_counter.h"

// Define la frecuencia para poder usar los delays
#define _XTAL_FREQ 8000000

/*
 * Constantes
 */

#define _tmr0_value 60

/*
 * Variables 
 */

uint8_t antirrebote1;
uint8_t antirrebote2;
uint8_t counter_button;
uint8_t counter_ADC;
uint8_t disps;
uint8_t bigger_value;
uint8_t smaller_value;
uint8_t result;

/*
 * Prototipos de funciones
 */
void setup(void);

/*
 * Interrupcion 
 */

void __interrupt() isr (void)
{
    if(PIR1bits.ADIF) {
        if(ADCON0bits.CHS == 5){    //si se encuentra en este canal, poner en la variable la respuesta en high
            counter_ADC = ADRESH;
        }
            
        PIR1bits.ADIF = 0;
    } 
    
    //Se llaman a las funciones de las librerías
    InterruptOCB();
    InterruptTMR0(bigger_value, smaller_value);
    
    
}

/*
 * Codigo Principal
 */
void main (void)
{
    setup();
    ADCON0bits.GO =1; //empezar una conversion inicial
    counter_button = 0;
    counter_ADC = 0;
    antirrebote1 = 0;
    antirrebote2 = 0;
    {
        // loop principal
        if (ADCON0bits.GO == 0) { // si esta en 0, revisa en qué canal está convirtiendo
            ADCON0bits.CHS = 5;
            ADCON0bits.GO =1; 
        }
       
        PORTA = counter_button;  //se muestra en el Puerto A el contador
        
        //Conversiones de ADC a hexadecimal 
        bigger_value = conversion_1(counter_ADC);   
        smaller_value = conversion_2(counter_ADC);   
        
        //Subrutina de alarma
        if (counter_ADC > counter_button){   //si el valor de ADC es mayor al del contador, la alarma se prende
            RB5 = 1;
        }
        
        else 
            RB5 = 0;
        
                       
        
    }
    
}

/*
 * Funciones
 */
void setup(void) 
{  
   // Configuraciones de entradas y salidas 
    ANSEL = 0b0010000;  //RA0, RA1 y RA2 RA3 como entradas analógicas para ADC 
    ANSELH = 0;
    
    TRISA = 0;
    TRISB = 0b00000011;        //3 botones: 
    TRISC = 0;
    TRISD = 0;
    TRISE = 0b001;
    
    //Weak Pull-ups
    OPTION_REGbits.nRBPU = 0; //entrada negada
    WPUB = 0b0011;
    
    IOCBbits.IOCB0 = 1;
    IOCBbits.IOCB1 = 1;
    
    
    //valores iniciales
    PORTB = 0;
    PORTA = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
    
    //Configuracion de oscilador
    OSCCONbits.IRCF = 0b0111; //4MHz
    OSCCONbits.SCS = 1; //ocsilador interno
    
    //Configuracion de Timer0
    //Timer0 Registers Prescaler= 256 - TMR0 Preset = 60 - Freq = 9.96 Hz - Period = 0.100352 seconds
    OPTION_REGbits.T0CS = 0;  // bit 5  TMR0 Clock Source Select bit...0 = Internal Clock (CLKO) 1 = Transition on T0CKI pin
    //OPTION_REGbits.T0SE = 0;  // bit 4 TMR0 Source Edge Select bit 0 = low/high 1 = high/low
    OPTION_REGbits.PSA = 0;   
    OPTION_REGbits.PS2 = 1;   // bits 2-0  PS2:PS0: Prescaler Rate Select bits (256)
    OPTION_REGbits.PS1 = 1;
    OPTION_REGbits.PS0 = 1;
    
    TMR0 = _tmr0_value;             // 25ms
    
    
   
     //Configuracion del ADC
    // 4MHz --> Fosc/8 se recomienda con 2us
    ADCON1bits.ADFM = 0; //justificado a la izquierda
    ADCON1bits.VCFG0 = 0; //VDD 
    ADCON1bits.VCFG1 = 0; //tierra
    
    ADCON0bits.ADCS = 0b01; //Fosc/8
    ADCON0bits.CHS = 5; //Canal 9 (AN9)
    ADCON0bits.ADON = 1; //change selection on 
    __delay_us(50);   //delay para que se cargue el capacitor en e modulo
    
    //Configuracion de las interrupciones
    INTCONbits.T0IF = 0;
    INTCONbits.T0IE = 1;
    INTCONbits.RBIF = 0;
    INTCONbits.RBIE = 1;
    PIR1bits.ADIF = 0; //apagar la bandera de ADC
    PIE1bits.ADIE = 1; //habilitar interrupcion analogica
    INTCONbits.PEIE = 1; //interrupciones perifericas
    INTCONbits.GIE  = 1;
   
    return;
    }