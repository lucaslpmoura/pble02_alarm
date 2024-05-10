#include "config.h"
#include "pic18f4520.h"
#include "pwm.h"
#include "timer.h"
#include "adc.h"
#include "lcd.h"
#include "keypad.h"
#include "event.h"
#include "var.h"
#include "stateMachine.h"
#include "output.h"
#include "rtc.h"
#include "led.h"

void main(void) {
     
    kpInit();
    lcdInit();
    timerInit();
    varInit();
    eventInit();
    adcInit();
    dsInit();
    ledInit();
    for (;;) {
        timerReset(1500);
       
        smLoop();
        
        timerWait();
    }
}