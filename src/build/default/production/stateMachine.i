# 1 "stateMachine.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files/Microchip/MPLABX/v6.05/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "stateMachine.c" 2
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
# 1 "stateMachine.c" 2

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
# 2 "stateMachine.c" 2

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
# 3 "stateMachine.c" 2

# 1 "./output.h" 1
# 10 "./output.h"
void outputInit(void);
void outputPrint(int numTela, int idioma);
# 4 "stateMachine.c" 2

# 1 "./lcd.h" 1
# 23 "./lcd.h"
 void lcdCommand(unsigned char cmd);
    void lcdCommand4bits(unsigned char cmd, unsigned char data);
 void lcdData(unsigned char valor);
    void lcdPosition(int line, int col);
 void lcdInit(void);
    void lcdInt(int);
    void lcdString(char msg[]);
# 5 "stateMachine.c" 2

# 1 "./keypad.h" 1


    unsigned char kpRead(void);
 void kpInit(void);
# 6 "stateMachine.c" 2


void smInit(void) {
    setState(STATE_HOME);
}

void smLoop(void) {
    unsigned char evento;


    evento = eventRead();

    switch (getState()) {
        case STATE_HOME:
            if (evento == EV_RIGHT) {
                setState(STATE_IDIOMA);
            }
            if (evento == EV_LEFT) {
                setState(STATE_ALARME_2);
            }
            break;
        case STATE_IDIOMA:


            if (evento == EV_ENTER) {
                setLanguage(getLanguage() + 1);
            }

            if (evento == EV_RIGHT) {
                setState(STATE_ALARME_1);
            }
            if (evento == EV_LEFT) {
                setState(STATE_HOME);
            }

            break;
        case STATE_ALARME_1:

            if (evento == EV_RIGHT) {
                setState(STATE_ALARME_2);
            }
            if (evento == EV_LEFT) {
                setState(STATE_IDIOMA);
            }


            if (evento == EV_ENTER) {
                setState(STATE_ALARME_1_ALTO);
            }
            break;
        case STATE_ALARME_2:

            if (evento == EV_RIGHT) {
                setState(STATE_HOME);
            }
            if (evento == EV_LEFT) {
                setState(STATE_ALARME_1);
            }


            if (evento == EV_ENTER) {
                setState(STATE_ALARME_2_ALTO);
            }
            break;
        case STATE_ALARME_1_ALTO:

            if (evento == EV_RIGHT || evento == EV_LEFT) {
                setState(STATE_ALARME_1_BAIXO);
            }
            if (evento == EV_UP) {
                setAlarmLevel(0, 0, getAlarmLevel(0, 0) + 1);
            }
            if (evento == EV_DOWN) {
                setAlarmLevel(0, 0, getAlarmLevel(0, 0) - 1);
            }

            if (evento == EV_ENTER) {
                setState(STATE_ALARME_1);
            }
            break;
        case STATE_ALARME_1_BAIXO:

            if (evento == EV_RIGHT || evento == EV_LEFT) {
                setState(STATE_ALARME_1_ALTO);
            }

            if (evento == EV_UP) {
                setAlarmLevel(0, 1, getAlarmLevel(0, 1) + 1);
            }
            if (evento == EV_DOWN) {
                setAlarmLevel(0, 1, getAlarmLevel(0, 1) - 1);
            }

            if (evento == EV_ENTER) {
                setState(STATE_ALARME_1);
            }
            break;
        case STATE_ALARME_2_ALTO:

            if (evento == EV_RIGHT || evento == EV_LEFT) {
                setState(STATE_ALARME_2_BAIXO);
            }
            if (evento == EV_UP) {
                setAlarmLevel(1, 0, getAlarmLevel(1, 0) + 1);
            }
            if (evento == EV_DOWN) {
                setAlarmLevel(1, 0, getAlarmLevel(1, 0) - 1);
            }

            if (evento == EV_ENTER) {
                setState(STATE_ALARME_2);
            }
            break;
        case STATE_ALARME_2_BAIXO:

            if (evento == EV_RIGHT || evento == EV_LEFT) {
                setState(STATE_ALARME_2_ALTO);
            }

            if (evento == EV_UP) {
                setAlarmLevel(1, 1, getAlarmLevel(1, 1) + 1);
            }
            if (evento == EV_DOWN) {
                setAlarmLevel(1, 1, getAlarmLevel(1, 1) - 1);
            }

            if (evento == EV_ENTER) {
                setState(STATE_ALARME_2);
            }
            break;


    }

    if (evento != EV_NOEVENT) {
        setTimer(0);
    }

    if (getTimer() < 2000) {
        setTimer(getTimer()+1);
    }
    if(getTimer() >= 2000){
        setState(STATE_HOME);
    }

    outputPrint(getState(), getLanguage());
}
