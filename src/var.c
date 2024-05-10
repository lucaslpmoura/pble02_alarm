#include "var.h"
#include "serial.h"
#include "rtc.h"
#define FLOAT_TO_INT(x) ((x)>=0?(int)((x)+0.5):(int)((x)-0.5))

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
                return dsReadData(ADDR_A1_HIGH);
                break;
            case 1:
                return dsReadData(ADDR_A1_LOW);
                break;
            default:
                return 0;
                break;
        }
    } else if (alarm == 1) {
        switch (level) {
            case 0:
                return dsReadData(ADDR_A2_HIGH);
                break;
            case 1:
                return dsReadData(ADDR_A2_LOW);
                break;
            default:
                return 0;
                break;
        }

    }
}

//1 HIGH : (0,0)
//1 LOW  : (0,1)
//2 HIGH : (1,0)
//2 LOW  : (1,1)

void setAlarmLevel(int alarm, int level, int newAlarmLevel) {
    switch (alarm) {
        case 0:
            switch (level) {
                case 0:
                    if (newAlarmLevel > dsReadData(ADDR_A1_LOW)) {
                        dsWriteData(newAlarmLevel > 100 ? 100 : newAlarmLevel, ADDR_A1_HIGH);
                    } else {
                        dsWriteData(dsReadData(ADDR_A1_LOW) + 1, ADDR_A1_HIGH);
                    }
                    break;
                case 1:
                    if (newAlarmLevel < dsReadData(ADDR_A1_HIGH)) {
                        dsWriteData(newAlarmLevel > 99 ? 99 : newAlarmLevel, ADDR_A1_LOW);
                    } else {
                        dsWriteData(dsReadData(ADDR_A1_HIGH) - 1, ADDR_A1_LOW);
                    }
                    break;
                default:
                    break;
            }
            break;
        case 1:
            switch (level) {
                case 0:
                    if (newAlarmLevel > dsReadData(ADDR_A2_LOW)) {
                        dsWriteData(newAlarmLevel > 100 ? 100 : newAlarmLevel, ADDR_A2_HIGH);
                    } else {
                        dsWriteData(dsReadData(ADDR_A2_LOW) + 1, ADDR_A2_HIGH);
                    }
                    break;
                case 1:
                    if (newAlarmLevel < dsReadData(ADDR_A2_HIGH)) {
                        dsWriteData(newAlarmLevel > 99 ? 99 : newAlarmLevel, ADDR_A2_LOW);
                    } else {
                        dsWriteData(dsReadData(ADDR_A2_HIGH) - 1, ADDR_A2_LOW);
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
    return dsReadData(ADDR_IDIOMA) % 2;
}

void setLanguage(int newLanguage) {
    dsWriteData(newLanguage % 2, ADDR_IDIOMA);
}

int getSensorValue(int sensor) {
    int value;

    if (sensor == 0) {
        value = adcRead(8);
    }
    if (sensor == 1) {
        value = adcRead(11);
    }

    return value;
}
