/* 
 * File:   stateMachine.h
 * Author: lucas
 *
 * Created on 4 de Junho de 2023, 18:55
 */

#ifndef STATEMACHINE_H
#define	STATEMACHINE_H

//estados da maquina de Estados

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


#endif	/* STATEMACHINE_H */

