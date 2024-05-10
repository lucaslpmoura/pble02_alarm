// -----------------------------------------------------------------------
//   Copyright (C) Rodrigo Almeida 2010
// -----------------------------------------------------------------------
//   Arquivo: lcd.c
//            Biblioteca de manipula??o do LCD
//   Autor:   Rodrigo Maximiano Antunes de Almeida
//            rodrigomax at unifei.edu.br
//   Licen?a: GNU GPL 2
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


#include "lcd.h"
#include "bits.h"
#include "serial.h"
#include <pic18f4550.h>
//portd
#define RS 0
#define EN 1
//portB
#define DB4 2 
#define DB5 3
#define DB6 4
#define DB7 5

void Delay40us(void) {
    unsigned char j;
    for (j = 0; j < 68; j++);
}

void Delay2ms(void) {
    unsigned char j, k;
    for (j = 0; j < 20; j++)
        for (k = 0; k < 178; k++);
}

void pulseEnable() {
    PORTAbits.RA1 = 1;
    PORTAbits.RA1 = 0;
}

void lcdCommand4bits(unsigned char cmd, unsigned char data) {
   
    if(data){
        PORTAbits.RA0 = 1;
    }else{
        PORTAbits.RA0 = 0;
    }
    
    
    if (bitTst(cmd, 7)) {
        PORTAbits.RA5 = 1;
    } else {
        PORTAbits.RA5 = 0;
    }


    if (bitTst(cmd, 6)) {
        PORTAbits.RA4 = 1;
    } else {
        PORTAbits.RA4 = 0;
    }


    if (bitTst(cmd, 5)) {
        PORTAbits.RA3 = 1;
    } else {
        PORTAbits.RA3 = 0;
    }


    if (bitTst(cmd, 4)) {
        PORTAbits.RA2 = 1;
    } else {
        PORTAbits.RA2 = 0;
    }

    pulseEnable();
}

void lcdCommand(unsigned char cmd) {
    lcdCommand4bits(cmd, 0);
    lcdCommand4bits(cmd << 4, 0);


    if ((cmd == 0x02) || (cmd == 0x01)) {
        Delay2ms();
    } else {
        Delay40us();
    }
}

void lcdData(unsigned char valor) {
    lcdCommand4bits(valor, 1);
    lcdCommand4bits(valor << 4, 1);    
    Delay40us();

}

void lcdInt(int val) {
    //lcdData((val / 10000) % 10 + 48);
    //lcdData((val / 1000) % 10 + 48);
    lcdData((val / 100) % 10 + 48);
    lcdData((val / 10) % 10 + 48);
    lcdData((val / 1) % 10 + 48);
}

void lcdString(char msg[]) {
    int i = 0;
	while (msg[i] != 0) {
		lcdData(msg[i]);
		i++;
	}
}

void lcdPosition(int line, int col) {
	if (line == 0) {
		lcdCommand(0x80 + (col % 16));
	}
	if (line == 1) {
		lcdCommand(0xC0 + (col % 16));
	}
}

void lcdInit(void) {
    unsigned char i;
    // configura??es de dire??o dos terminais
    TRISA = 0x00;   
    bitClr(SPPCFG, 5);
    ADCON1 = 0b00001111; //apenas

    
    PORTAbits.RA0 = 0;
    // garante inicializa??o do LCD (+-15ms)
    for (i = 0; i < 7; i++)
        Delay2ms();

    //precisa enviar 4x pra garantir 8 bits
    lcdCommand4bits(0x30, 0); //8bits, 2 linhas, 5x8
    Delay2ms();

    lcdCommand4bits(0x30, 0); //8bits, 2 linhas, 5x8
    Delay2ms();

    lcdCommand4bits(0x30, 0); //8bits, 2 linhas, 5x8
    Delay2ms();

    lcdCommand4bits(0x20, 0); //4bits
    Delay2ms();

    lcdCommand(0x28); //4bits
    lcdCommand(0x06); //modo incremental
    lcdCommand(0x0F); //display e cursor on, com blink
    lcdCommand(0x01); //limpar display
}