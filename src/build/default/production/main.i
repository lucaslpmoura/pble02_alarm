# 1 "main.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files/Microchip/MPLABX/v6.05/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "main.c" 2
# 1 "./config.h" 1
# 26 "./config.h"
#pragma config FOSC = HS
#pragma config FCMEN = OFF
#pragma config IESO = OFF
#pragma config PWRT = OFF
#pragma config BOR = OFF
#pragma config BORV = 46
#pragma config WDT=OFF
#pragma config WDTPS = 1
#pragma config MCLRE=ON
#pragma config LPT1OSC = OFF
#pragma config PBADEN = ON
#pragma config CCP2MX = ON
#pragma config STVREN = OFF
#pragma config LVP=OFF
#pragma config XINST = OFF
#pragma config DEBUG = OFF

#pragma config CP0 = OFF
#pragma config CP1 = OFF
#pragma config CP2 = OFF
#pragma config CP3 = OFF
#pragma config CPB = OFF
#pragma config CPD = OFF

#pragma config WRT0 = OFF
#pragma config WRT1 = OFF
#pragma config WRT2 = OFF
#pragma config WRT3 = OFF
#pragma config WRTB = OFF
#pragma config WRTC = OFF
#pragma config WRTD = OFF

#pragma config EBTR0 = OFF
#pragma config EBTR1 = OFF
#pragma config EBTR2 = OFF
#pragma config EBTR3 = OFF
#pragma config EBTRB = OFF
# 1 "main.c" 2

# 1 "./pic18f4520.h" 1
# 2 "main.c" 2

# 1 "./pwm.h" 1
# 23 "./pwm.h"
 void pwmSet(unsigned char porcento);
 void pwmFrequency(unsigned int freq);
 void pwmInit(void);
# 3 "main.c" 2

# 1 "./timer.h" 1
# 23 "./timer.h"
 char timerEnded(void);
 void timerWait(void);

 void timerReset(unsigned int tempo);
 void timerInit(void);
# 4 "main.c" 2

# 1 "./adc.h" 1
# 23 "./adc.h"
 void adcInit(void);
 int adcRead(unsigned int channel);
# 5 "main.c" 2

# 1 "./lcd.h" 1
# 23 "./lcd.h"
 void lcdCommand(unsigned char cmd);
    void lcdCommand4bits(unsigned char cmd, unsigned char data);
 void lcdData(unsigned char valor);
    void lcdPosition(int line, int col);
 void lcdInit(void);
    void lcdInt(int);
    void lcdString(char msg[]);
# 6 "main.c" 2

# 1 "./keypad.h" 1


    unsigned char kpRead(void);
 void kpInit(void);
# 7 "main.c" 2

# 1 "./event.h" 1
# 11 "./event.h"
enum{
    EV_UP,
    EV_DOWN,
    EV_LEFT,
    EV_RIGHT,
    EV_ENTER,
    EV_NOEVENT
};
void eventInit(void);
unsigned int eventRead(void);
void processarProtocolo(void);
# 8 "main.c" 2

# 1 "./var.h" 1
# 22 "./var.h"
void varInit(void);

char getState(void);
void setState(char newState);
int getTimer(void);
void setTimer(int);

int getAlarmLevel(int alarm, int level);
void setAlarmLevel(int alarm, int level, int newAlarmLevel);
int checkAlarm(int alarm, int level);

int getLanguage(void);
void setLanguage(int newLanguage);

int getSensorValue(int sensor);
# 9 "main.c" 2

# 1 "./stateMachine.h" 1
# 13 "./stateMachine.h"
enum {
    STATE_HOME,
    STATE_IDIOMA,
    STATE_ALARME_1,
    STATE_ALARME_2,
    STATE_ALARME_1_ALTO,
    STATE_ALARME_1_BAIXO,
    STATE_ALARME_2_ALTO,
    STATE_ALARME_2_BAIXO,
    STATE_FIM
};


void smInit(void);
void smLoop(void);
# 10 "main.c" 2

# 1 "./output.h" 1
# 10 "./output.h"
void outputInit(void);
void outputPrint(int numTela, int idioma);
# 11 "main.c" 2

# 1 "./rtc.h" 1
# 13 "./rtc.h"
 void dsInit(void);
 void dsStartClock(void);
 void dsStopClock(void);
 int dec2bcd(int value);
 int bcd2dec(int value);
 void dsWriteData(unsigned char value, int address);
 int dsReadData(int address);
    void setHours(int hours);
    void setMinutes(int minutes);
    void setSeconds(int seconds);
    int getHours(void);
    int getMinutes(void);
    int getSeconds(void);
# 12 "main.c" 2

# 1 "./led.h" 1
# 11 "./led.h"
void ledInit();
void ledOn(int pos);
void ledOff(int pos);
void ledBlink(int pos);
# 13 "main.c" 2


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
