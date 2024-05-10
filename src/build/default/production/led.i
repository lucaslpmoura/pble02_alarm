# 1 "led.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files/Microchip/MPLABX/v6.05/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "led.c" 2
# 1 "./io.h" 1
# 12 "./io.h"
enum pin_label{
    PIN_A0,PIN_A1,PIN_A2,PIN_A3,PIN_A4,PIN_A5,PIN_A6,PIN_A7,
    PIN_B0,PIN_B1,PIN_B2,PIN_B3,PIN_B4,PIN_B5,PIN_B6,PIN_B7,
    PIN_C0,PIN_C1,PIN_C2,PIN_C3,PIN_C4,PIN_C5,PIN_C6,PIN_C7,
    PIN_D0,PIN_D1,PIN_D2,PIN_D3,PIN_D4,PIN_D5,PIN_D6,PIN_D7,
    PIN_E0,PIN_E1,PIN_E2,PIN_E3,PIN_E4,PIN_E5,PIN_E6,PIN_E7
};
# 54 "./io.h"
void digitalWrite(int pin, int value);
int digitalRead(int pin);
void pinMode(int pin, int type);
# 1 "led.c" 2

# 1 "./bits.h" 1
# 2 "led.c" 2

# 1 "./PIC18F4520.h" 1
# 3 "led.c" 2


void ledInit() {
    (*(volatile __near unsigned char*)0xF94) = 0x00;
    digitalWrite(PIN_C1, 0);
    digitalWrite(PIN_C2, 0);
}

void ledOn(int pos) {
    switch (pos) {
        case 1:
            digitalWrite(PIN_C1, 1);
            break;
        case 2:
            digitalWrite(PIN_C2, 1);
            break;
    }

}

void ledOff(int pos) {
    switch (pos) {
        case 1:
            digitalWrite(PIN_C1, 0);
            break;
        case 2:
            digitalWrite(PIN_C2, 0);
            break;
    }
}

void ledBlink(int pos) {
    switch (pos) {
        case 1:
            if (digitalRead(PIN_C1)) {
                digitalWrite(PIN_C1, 0);
            } else {
                digitalWrite(PIN_C1, 1);
            }
            break;
        case 2:
            if (digitalRead(PIN_C2)) {
                digitalWrite(PIN_C2, 0);
            } else {
                digitalWrite(PIN_C2, 1);
            }
            break;
    }

}
