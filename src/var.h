/* 
 * File:   var.h
 * Author: lucas
 *
 * Created on 4 de Junho de 2023, 18:54
 */

#ifndef VAR_H
#define	VAR_H


//enderecos de memoria para os alarmes
#define ADDR_A1_LOW	 0x20 
#define ADDR_A1_HIGH 0x21
#define ADDR_A2_LOW  0x22
#define ADDR_A2_HIGH 0x23


//endereco de memoria do idioma
#define ADDR_IDIOMA	0x30

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
#endif	/* VAR_H */

