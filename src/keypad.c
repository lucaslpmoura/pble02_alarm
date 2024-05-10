#include "keypad.h"
#include "so.h"
#include "io.h"
#include "bits.h"

#include <pic18f4550.h>

//Ordem dos botões em relação a placa 
//SW2 = PORTD4 R : 5
//SW3 = PORTD3 L : 4
//SW4 = PORTD2 S : 3
//SW5 = PORTD1 U : 2
//SW6 = PORTD0 D : 1
static unsigned char valor = 0x00;
static unsigned char valorAntigo = 0x00;

unsigned char j;

unsigned char kpRead(void) {
    
    for (j = 0; j < 5; j++)
    {
        if (!bitTst(PORTD, j))
        {
            valor = j + 1;
        }
    }
    if(valor == valorAntigo){
        valor = 0;
    }else{
        valorAntigo = valor;
    }
    
    return valor;
}

void kpInit(void) {
    TRISE = 0x00;
    bitSet(PORTE, 7);
    pinMode(PULL_UP_ENABLE, OUTPUT);
    pinMode(KEYPAD_1_PIN, INPUT);
    pinMode(KEYPAD_2_PIN, INPUT);
    pinMode(KEYPAD_3_PIN, INPUT);
    pinMode(KEYPAD_4_PIN, INPUT);
    pinMode(KEYPAD_5_PIN, INPUT);
}
