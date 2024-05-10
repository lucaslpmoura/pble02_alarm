#include "var.h"
#include "stateMachine.h"
#include "event.h"
#include "output.h"
#include "lcd.h"
#include "keypad.h"

void smInit(void) {
    setState(STATE_HOME);
}

void smLoop(void) {
    unsigned char evento;

    //m?quina de estados
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

            //execu??o de atividade
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

            //gest?o da maquina de estado
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

            //gest?o da maquina de estado
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
            //gest?o da maquina de estado
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
            //gest?o da maquina de estado
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
            //gest?o da maquina de estado
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
            //gest?o da maquina de estado
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

