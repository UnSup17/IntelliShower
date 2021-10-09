/* 
 * File:   keypad.h
 * Author: UnSup
 *
 * Created on 4 de octubre de 2021, 10:14 PM
 */

#ifndef KEYPAD_H
#define	KEYPAD_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "fuses.h"

#define write_port LATB             /* latch register to write data on port */
#define read_port PORTB             /* PORT register to read data of port */
#define Direction_Port TRISB
unsigned char col_loc,rowloc,temp_col;

unsigned char keypad[4][3]= {'1','2','3',
                             '4','5','6',
                             '7','8','9',
                             '*','0','#'};

unsigned char keyfind();

#ifdef	__cplusplus
}
#endif

#endif	/* KEYPAD_H */

