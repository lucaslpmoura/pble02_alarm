#include "output.h"
#include "lcd.h"
#include "stateMachine.h"
#include "var.h"
#include "serial.h"
#include "led.h"


#define NUM_IDIOMAS 2
#define NUM_ESTADOS STATE_FIM

//msgs com 16 caracteres
//1 msg por estado (apenas linha de cima)
static char * msgsL1[NUM_ESTADOS][NUM_IDIOMAS] = {
    {"SENSOR 1:", "SENSOR 1:"}, //STATE_HOME
    {"Alterar idioma ", "Change language"}, //STATE_LANGUAGE
    {"Alterar alarme ", "Change alarm    "}, //STATE_ALARM_1
    {"Alterar alarme ", "Change alarm    "}, //STATE_ALARM_2
    {"Alarme 1 alto  ", "Alarm 1 High    "}, //STATE_ALARM_1_ALTO
    {"Alarme 1 baixo ", "Alarm 1 Low     "}, //STATE_ALARM_1_BAIXO
    {"Alarme 2 alto  ", "Alarm 2 High    "}, //STATE_ALARM_2_ALTO
    {"Alarme 2 baixo ", "Alarm 2 Low     "}, //STATE_ALARM_2_BAIXO
};

static char * msgsL2[NUM_ESTADOS][NUM_IDIOMAS] = {
    {"SENSOR 2:", "SENSOR 2:"},
    {"Portugues      ", "English        "},
    {"Sensor 1       ", "Sensor 1       "},
    {"Sensor 2       ", "Sensor 2       "},
    {"Valor : ", "Value : "},
    {"Valor : ", "Value : "},
    {"Valor : ", "Value : "},
    {"Valor : ", "Value : "},
};

static char * lcdAlerts[2][NUM_IDIOMAS] = {
    {"  !A", "  !H"},
    {"  !B", "  !L"}
};

static char * serialAlerts[2][NUM_IDIOMAS] = {
    {"ALERTA: Limite ALTO Atingido", "WARNING: HIGH Threshold Reached"},
    {"ALERTA: Limite BAIXO Atingido", "WARNING: LOW Threshold Reached"},
};

static int tela_ant = 0;

void outputInit(void) {
    lcdInit();
}

void outputPrint(int numTela, int idioma) {
    //serialSend('\12');
    if (numTela != tela_ant) {
        lcdCommand(0x01);
        tela_ant = numTela;
    }
    if (numTela == STATE_HOME) {
        lcdCommand(0x80);

        //Linha 1
        serialSend('\12');
        lcdString(msgsL1[numTela][idioma]);
        lcdInt(getSensorValue(0));
        serialString(msgsL1[numTela][idioma]);
        serialInt(getSensorValue(0));
        serialSend('\12');
        if (checkAlarm(0, 0)) {
            lcdString(lcdAlerts[0][idioma]);
            serialString(serialAlerts[0][idioma]);
            serialSend('\12');
            ledBlink(1);
        } else if (checkAlarm(0, 1)) {
            lcdString(lcdAlerts[1][idioma]);
            serialString(serialAlerts[1][idioma]);
            serialSend('\12');
            ledBlink(1);
        } else {
            lcdString("    ");
            ledOff(1);
        }
        lcdCommand(0xC0);

        //Linha 2
        serialSend('\12');
        lcdString(msgsL2[numTela][idioma]);
        lcdInt(getSensorValue(1));
        serialString(msgsL2[numTela][idioma]);
        serialInt(getSensorValue(1));
        serialSend('\12');
        if (checkAlarm(1, 0)) {
            lcdString(lcdAlerts[0][idioma]);
            serialString(serialAlerts[0][idioma]);
            serialSend('\12');
            ledBlink(2);
            serialInt(checkAlarm(1, 0));
        } else if (checkAlarm(1, 1)) {
            lcdString(lcdAlerts[1][idioma]);
            serialString(serialAlerts[1][idioma]);
            serialSend('\12');
            ledBlink(2);
        } else {
            lcdString("    ");
            ledOff(2);
        }
    }
    
    if (numTela == STATE_IDIOMA) {
        lcdCommand(0x80);
        lcdString(msgsL1[numTela][idioma]);
        lcdCommand(0xC0);
        lcdString(msgsL2[numTela][idioma]);
        
        serialSend('\12');
        serialString(msgsL1[numTela][idioma]);
        serialSend('\12');
        serialString(msgsL2[numTela][idioma]);
    }

    if (numTela == STATE_ALARME_1) {
        lcdCommand(0x80);
        lcdString(msgsL1[numTela][idioma]);
        lcdCommand(0xC0);
        lcdString(msgsL2[numTela][idioma]);
        serialSend('\12');
        serialString(msgsL1[numTela][idioma]);
        serialSend('\12');
        serialString(msgsL2[numTela][idioma]);
    }
    if (numTela == STATE_ALARME_2) {
        lcdCommand(0x80);
        lcdString(msgsL1[numTela][idioma]);
        lcdCommand(0xC0);
        lcdString(msgsL2[numTela][idioma]);

        serialSend('\12');
        serialString(msgsL1[numTela][idioma]);
        serialSend('\12');
        serialString(msgsL2[numTela][idioma]);
    }

    if (numTela == STATE_ALARME_1_ALTO) {
        lcdCommand(0x80);
        lcdString(msgsL1[numTela][idioma]);
        lcdCommand(0xC0);
        lcdString(msgsL2[numTela][idioma]);
        lcdInt(getAlarmLevel(0, 0));

        serialSend('\12');
        serialString(msgsL1[numTela][idioma]);
        serialSend('\12');
        serialString(msgsL2[numTela][idioma]);
        serialInt(getAlarmLevel(0, 0));
    }
 
    if (numTela == STATE_ALARME_1_BAIXO) {
        lcdCommand(0x80);
        lcdString(msgsL1[numTela][idioma]);
        lcdCommand(0xC0);
        lcdString(msgsL2[numTela][idioma]);
        lcdInt(getAlarmLevel(0, 1));

        serialSend('\12');
        serialString(msgsL1[numTela][idioma]);
        serialSend('\12');
        serialString(msgsL2[numTela][idioma]);
        serialInt(getAlarmLevel(0, 1));
    }

    if (numTela == STATE_ALARME_2_ALTO) {
        lcdCommand(0x80);
        lcdString(msgsL1[numTela][idioma]);
        lcdCommand(0xC0);
        lcdString(msgsL2[numTela][idioma]);
        lcdInt(getAlarmLevel(1, 0));
        //retornar valor do sensor
        serialSend('\12');
        serialString(msgsL1[numTela][idioma]);
        serialSend('\12');
        serialString(msgsL2[numTela][idioma]);
        serialInt(getAlarmLevel(1, 0));

    }
    if (numTela == STATE_ALARME_2_BAIXO) {
        lcdCommand(0x80);
        lcdString(msgsL1[numTela][idioma]);
        lcdCommand(0xC0);
        lcdString(msgsL2[numTela][idioma]);
        lcdInt(getAlarmLevel(1, 1));

        serialSend('\12');
        serialString(msgsL1[numTela][idioma]);
        serialSend('\12');
        serialString(msgsL2[numTela][idioma]);
        serialInt(getAlarmLevel(1, 1));
    }
}


