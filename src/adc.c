// -----------------------------------------------------------------------
//   Copyright (C) Rodrigo Almeida 2010
// -----------------------------------------------------------------------
//   Arquivo: adc.c
//            Biblioteca do conversor AD para o PIC18F4520
//   Autor:   Rodrigo Maximiano Antunes de Almeida
//            rodrigomax at unifei.edu.br
//   Licença: GNU GPL 2
// -----------------------------------------------------------------------
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation; version 2 of the License.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
// -----------------------------------------------------------------------

#include "adc.h"
#include <pic18f4520.h>
#include "io.h"
#include "bits.h"

#define DEC_CAST 10.24
#define FLOAT_TO_INT(x) ((x)>=0?(int)((x)+0.5):(int)((x)-0.5))

void adcInit(void) {
    pinMode(PIN_B2, INPUT);
    pinMode(PIN_E2, INPUT);
    pinMode(PIN_B4, INPUT);

    bitSet(ADCON0, 0); //liga ADC
    //config an0-2 como analógico
    ADCON2 = 0b10101010; //FOSC /32, 12 TAD, Alinhamento à direita e tempo de conv = 12 TAD
    
}

int adcRead(unsigned int channel) {
    unsigned int ADvalor;
    ADCON1 = 0b00000011; //AN11
   
    ADCON0 &= 0b11000011; //zera os bits do canal
    if(channel == 7){
        ADCON0 |= 0b00011100;
    }else if (channel == 8) {
        ADCON0 |= 0b00100000;
        //ADCON0 |= channel << 2;
    }else if( channel == 11){
        ADCON0 |= 0b00101100;
    }
    
    ADCON0 |= 0b00000010; //inicia conversao

    while (bitTst(ADCON0, 1)); // espera terminar a conversão;

    ADvalor = ADRESH; // le o resultado
    ADvalor <<= 8;
    ADvalor += ADRESL;
    
    ADCON1 = 0b00001111; //tudo dig
   
    return FLOAT_TO_INT(ADvalor/DEC_CAST);
}