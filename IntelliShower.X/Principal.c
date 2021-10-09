/* 
 * File:   Principal.c
 * Author: 57322
 *
 * Created on 9 de agosto de 2021, 09:54 AM
 */

#include <xc.h>
#include <stdio.h>
#include <pic18f4550.h>
#include "adc_lib.h"
#include "fuses.h"
#include "LCD.h"
#include <stdint.h>
#include "adc_con.h"
#include "keypad.h"

#define X_TAL_FREQ 48000000

#define LED_ROJO LATC0
#define LED_VERDE LATC1

#define RELAY LATA1

#define ON 1
#define OFF 0

#define write_port LATB             /* latch register to write data on port */
#define read_port PORTB             /* PORT register to read data of port */
#define Direction_Port TRISB

double temp = 0.0;
char lm35[16];
char userTemp[2] = {' ', ' '};
uint16_t value_adc;
unsigned char idx = 0;

void alarmaPositiva();
void alarmaNegativa();

void main(void) {
    ADCON1 = 0b00001111;
    
    TRISA = 0b00000001;// salida 7-1, 0 entrada puerto A
    TRISB = 0xf0;
    TRISC = 0x00;
    TRISD = 0x00;// salida puerto D
    
    OSCCONbits.IRCF = 0b111; //Configura oscilador interno (FOSC = 8Mhz)
    OSCCONbits.SCS = 0b10; // Oscilador del sistema = Fosc interno
    
    OSCCON = 0x72; //frec 8Mhz, oscilador interno
    
    adc_initcon();
    
    RBPU = 0; /* activate pull-up resistor*/
    LCD_Init(); /* initialize LCD16x2 in 4-bit mode */
    
    char char_userTemp;
    while (1) {
        value_adc = adc_reader(); //  Lectura de valor AD.*/;
        
        if (idx < 3){
            LCD_Clear();
            LCD_String_xy(0,0,"Insert temp");
            LCD_Command(0xC0);                  /* display pressed key on 2nd line of LCD */
            do{
                char_userTemp = keyfind();              /* find a pressed key */
                LCD_Char(char_userTemp);                /* display pressed key on LCD16x2 */
                userTemp[idx] = char_userTemp;
                if (userTemp[0] < '2' || userTemp[0] > '3' || (userTemp[0] == '3' && userTemp[1] > '8')){
                    alarmaNegativa();
                    char_userTemp = '#';
                    idx = 3;
                } 
                idx++;
            }while(char_userTemp != '#');
            idx = 0;
            alarmaPositiva();
        }
        int decena = (userTemp[0] - '0') * 10;
        int number = decena + (userTemp[1] - '0');
//        int number = ((int)userTemp[0] * 10) + (int)userTemp[1];
        
        if ((value_adc*0.4882) < number) {
            RELAY = ON;
        } else {
            RELAY = OFF;
        }
        
//        temp = value_adc*0.4882;
//        if (temp < 38) {
//            PORTC = 0b00000010;
//        }
//        else {
//            PORTC = 0b00000001;
//        }
//        sprintf(lm35, "%.2lf", temp);
//        LCD_String_xy(0,0, "Temperatura");
//        __delay_ms(500);
//        LCD_Command(0xC0);
//        LCD_String(lm35);
//        __delay_ms(500);
    }
}

void alarmaPositiva() {
    LCD_Clear();
    LED_VERDE = ON;
    LCD_String_xy(0,0,"OKAY");
    __delay_ms(500);
    LED_VERDE = OFF;
    LCD_Clear();
}

void alarmaNegativa() {
    LCD_Clear();
    LED_ROJO = ON;
    LCD_String_xy(0,0,"ERROR");
    __delay_ms(500);
    LED_ROJO = OFF;
    LCD_Clear();
}
