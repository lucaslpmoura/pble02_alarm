/* 
 * File:   event.h
 * Author: lucas
 *
 * Created on 4 de Junho de 2023, 18:42
 */

#ifndef EVENT_H
#define	EVENT_H

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
#endif	/* EVENT_H */