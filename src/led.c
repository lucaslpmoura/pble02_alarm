#include "io.h"
#include "bits.h"
#include "PIC18F4520.h"

void ledInit() {
    TRISC = 0x00;
    digitalWrite(LED_1, 0);
    digitalWrite(LED_2, 0);
}

void ledOn(int pos) {
    switch (pos) {
        case 1:
            digitalWrite(LED_1, 1);
            break;
        case 2:
            digitalWrite(LED_2, 1);
            break;
    }

}

void ledOff(int pos) {
    switch (pos) {
        case 1:
            digitalWrite(LED_1, 0);
            break;
        case 2:
            digitalWrite(LED_2, 0);
            break;
    }
}

void ledBlink(int pos) {
    switch (pos) {
        case 1:
            if (digitalRead(LED_1)) {
                digitalWrite(LED_1, 0);
            } else {
                digitalWrite(LED_1, 1);
            }
            break;
        case 2:
            if (digitalRead(LED_2)) {
                digitalWrite(LED_2, 0);
            } else {
                digitalWrite(LED_2, 1);
            }
            break;
    }

}
