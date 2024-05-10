# 1 "output.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files/Microchip/MPLABX/v6.05/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "output.c" 2
# 1 "./output.h" 1
# 10 "./output.h"
void outputInit(void);
void outputPrint(int numTela, int idioma);
# 1 "output.c" 2

# 1 "./lcd.h" 1
# 23 "./lcd.h"
 void lcdCommand(unsigned char cmd);
    void lcdCommand4bits(unsigned char cmd, unsigned char data);
 void lcdData(unsigned char valor);
    void lcdPosition(int line, int col);
 void lcdInit(void);
    void lcdInt(int);
    void lcdString(char msg[]);
# 2 "output.c" 2

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
# 3 "output.c" 2

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
# 4 "output.c" 2

# 1 "./serial.h" 1
# 23 "./serial.h"
void serialInt(int val);
void serialString(char msg[]);
void serialSend(unsigned char c);
unsigned char serialRead(void);
void serialInit(void);
# 5 "output.c" 2

# 1 "./led.h" 1
# 11 "./led.h"
void ledInit();
void ledOn(int pos);
void ledOff(int pos);
void ledBlink(int pos);
# 6 "output.c" 2








static char * msgsL1[STATE_FIM][2] = {
    {"SENSOR 1:", "SENSOR 1:"},
    {"Alterar idioma ", "Change language"},
    {"Alterar alarme ", "Change alarm    "},
    {"Alterar alarme ", "Change alarm    "},
    {"Alarme 1 alto  ", "Alarm 1 High    "},
    {"Alarme 1 baixo ", "Alarm 1 Low     "},
    {"Alarme 2 alto  ", "Alarm 2 High    "},
    {"Alarme 2 baixo ", "Alarm 2 Low     "},
};

static char * msgsL2[STATE_FIM][2] = {
    {"SENSOR 2:", "SENSOR 2:"},
    {"Portugues      ", "English        "},
    {"Sensor 1       ", "Sensor 1       "},
    {"Sensor 2       ", "Sensor 2       "},
    {"Valor : ", "Value : "},
    {"Valor : ", "Value : "},
    {"Valor : ", "Value : "},
    {"Valor : ", "Value : "},
};

static char * lcdAlerts[2][2] = {
    {"  !A", "  !H"},
    {"  !B", "  !L"}
};

static char * serialAlerts[2][2] = {
    {"ALERTA: Limite ALTO Atingido", "WARNING: HIGH Threshold Reached"},
    {"ALERTA: Limite BAIXO Atingido", "WARNING: LOW Threshold Reached"},
};

static int tela_ant = 0;

void outputInit(void) {
    lcdInit();
}

void outputPrint(int numTela, int idioma) {

    if (numTela != tela_ant) {
        lcdCommand(0x01);
        tela_ant = numTela;
    }
    if (numTela == STATE_HOME) {
        lcdCommand(0x80);


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
