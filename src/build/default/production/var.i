# 1 "var.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files/Microchip/MPLABX/v6.05/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "var.c" 2
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
# 1 "var.c" 2

# 1 "./serial.h" 1
# 23 "./serial.h"
void serialInt(int val);
void serialString(char msg[]);
void serialSend(unsigned char c);
unsigned char serialRead(void);
void serialInit(void);
# 2 "var.c" 2

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
# 3 "var.c" 2



static char state;
static int timer;

void varInit(void) {
    state = 0;
    timer = 0;
    if(getAlarmLevel(0,0) > 100) setAlarmLevel(0,0, 100);
    if(getAlarmLevel(0,1) > 100) setAlarmLevel(0,1, 0);
    if(getAlarmLevel(1,0) > 100) setAlarmLevel(1,0, 100);
    if(getAlarmLevel(1,1) > 100) setAlarmLevel(1,1, 0);
}

char getState(void) {
    return state;
}

void setState(char newState) {
    state = newState;
}

int getTimer(void) {

    return timer;
}

void setTimer(int val) {
    timer = val;
}

int getAlarmLevel(int alarm, int level) {
    if (alarm == 0) {
        switch (level) {
            case 0:
                return dsReadData(0x21);
                break;
            case 1:
                return dsReadData(0x20);
                break;
            default:
                return 0;
                break;
        }
    } else if (alarm == 1) {
        switch (level) {
            case 0:
                return dsReadData(0x23);
                break;
            case 1:
                return dsReadData(0x22);
                break;
            default:
                return 0;
                break;
        }

    }
}






void setAlarmLevel(int alarm, int level, int newAlarmLevel) {
    switch (alarm) {
        case 0:
            switch (level) {
                case 0:
                    if (newAlarmLevel > dsReadData(0x20)) {
                        dsWriteData(newAlarmLevel > 100 ? 100 : newAlarmLevel, 0x21);
                    } else {
                        dsWriteData(dsReadData(0x20) + 1, 0x21);
                    }
                    break;
                case 1:
                    if (newAlarmLevel < dsReadData(0x21)) {
                        dsWriteData(newAlarmLevel > 99 ? 99 : newAlarmLevel, 0x20);
                    } else {
                        dsWriteData(dsReadData(0x21) - 1, 0x20);
                    }
                    break;
                default:
                    break;
            }
            break;
        case 1:
            switch (level) {
                case 0:
                    if (newAlarmLevel > dsReadData(0x22)) {
                        dsWriteData(newAlarmLevel > 100 ? 100 : newAlarmLevel, 0x23);
                    } else {
                        dsWriteData(dsReadData(0x22) + 1, 0x23);
                    }
                    break;
                case 1:
                    if (newAlarmLevel < dsReadData(0x23)) {
                        dsWriteData(newAlarmLevel > 99 ? 99 : newAlarmLevel, 0x22);
                    } else {
                        dsWriteData(dsReadData(0x23) - 1, 0x22);
                    }
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

int checkAlarm(int alarm, int level) {
    if (level == 0) {
        if (getAlarmLevel(alarm, level) <= getSensorValue(alarm)) {
            return 1;
        }else{
            return 0;
        }
    } else if(level == 1) {
        if (getAlarmLevel(alarm, level) >= getSensorValue(alarm)) {
            return 1;
        }else{
            return 0;
        }
    }
}

int getLanguage(void) {
    return dsReadData(0x30) % 2;
}

void setLanguage(int newLanguage) {
    dsWriteData(newLanguage % 2, 0x30);
}

int getSensorValue(int sensor) {
    int value;

    if (sensor == 0) {
        value = adcRead(7);
    }
    if (sensor == 1) {
        value = adcRead(11);
    }

    return value;
}
