/* 
 * File:   adc_lib.h
 * Author: ASUS
 *
 * Created on 28 de septiembre de 2021, 12:38
 */

#ifndef ADC_LIB_H
#define	ADC_LIB_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    void adc_init ();
    unsigned char adc_read();

#ifdef	__cplusplus
}
#endif

#endif	/* ADC_LIB_H */

