#include    <xc.h>
#include    "fuses.h"
#include "adc_lib.h"

void main(void) {
    TRISD = 0x00;// salida puerto D
    TRISA = 0xFF;//entrada puerto A 
    
    OSCCONbits.IRCF = 0b111; //Configura oscilador interno (FOSC = 8Mhz)
    OSCCONbits.SCS = 0b10; // Oscilador del sistema = Fosc interno
    
    OSCCON = 0x72;
    
    adc_init();
    
    while (1) {
        
        ADCON0bits.GO_DONE = 1; //  Inicia la conversión AD.
        while (ADCON0bits.GO_DONE); //  Espera a que termine la conversión AD.
     // LATD = ADRESH;
        LATD = adc_read(); //  Lectura de valor AD.
        if(LATD > 1){
            LATD7 = 1;  
        }else {
            LATD7 = 0;  
        }
        
    }
}
