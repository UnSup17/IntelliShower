#include <xc.h>
#include "adc_lib.h"

void adc_init (){
    ADCON1bits.PCFG = 0b1110; //  Configura el Puerto como Entrada Anal�gica.
    ADCON1bits.VCFG = 0b00; //  Selecciona Voltajes de Referencia (5v-0v).
    ADCON0bits.CHS = 0b0000; //  Selecciona el Canal Anal�gico.
    ADCON2bits.ACQT = 0b010; //  Tiempo de Adquisici�n 4Tad.
    ADCON2bits.ADCS = 0b001; //  Tiempo de Conversi�n Fosc/8.
    ADCON2bits.ADFM = 0; //  Justificaci�n Izquierda (modo-8bits).
    ADCON0bits.ADON = 1; //  Habilita el M�dulo AD.
    }

unsigned char adc_read(){
    ADCON0bits.GO_DONE = 1; //  Inicia la COnversi� AD.
    while (ADCON0bits.GO_DONE); //  Espera a que termine la conversi�n AD.
    return ADRESH; //  Lectura de valor AD    
}

