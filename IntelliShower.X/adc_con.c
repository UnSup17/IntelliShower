#include <xc.h>
#include "adc_con.h"

void adc_initcon(){
    //ADC = 10bits, Tad = 1us, Tacq = 4us, Vref = 5v-0v, RA=ANALOG
    ADCON1bits.PCFG = 0b1110; //  Configura el Puerto como Entrada Anal�gica.
    ADCON1bits.VCFG = 0b00; //  Selecciona Voltajes de Referencia (5v-0v).
    ADCON0bits.CHS = 0b0000; //  Selecciona el Canal Anal�gico.
    ADCON2bits.ACQT = 0b010; //  Tiempo de Adquisici�n 4Tad.
    ADCON2bits.ADCS = 0b001; //  Tiempo de Conversi�n Fosc/8.
    ADCON2bits.ADFM = 1; //  Justificaci�n derecha (modo-10bits).
    ADCON0bits.ADON = 1; //  Habilita el M�dulo AD.
}

unsigned int adc_reader(void) {
    unsigned int value_adc = 0;
    ADCON0bits.GO_DONE = 1; //Inicia la COnversi� AD.
    while (ADCON0bits.GO_DONE); //  Espera a que termine la conversi�n AD.
    value_adc = ADRESH; //  Lectura de valor AD.
    value_adc = (value_adc << 8) + ADRESL;
    return value_adc;  
}