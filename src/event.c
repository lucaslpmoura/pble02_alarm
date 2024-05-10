#include "event.h"
#include <pic18f4550.h>
#include <string.h>
#include "serial.h"
#include "keypad.h"
#include "bits.h"
#include "var.h"
#define SIZE 32

static unsigned int key_ant;
static unsigned char protocolo[SIZE];
static unsigned int protocolo_index;

void eventInit(void) {
    serialInit();
    kpInit();
    key_ant = 0;
}

unsigned int eventRead(void) {
    unsigned int key;
    unsigned char serial_command;
    int ev = EV_NOEVENT;

    key = kpRead();

    if (key != key_ant) {
        if (key == 5) {
            ev = EV_RIGHT;
        }

        if (key == 4) {
            ev = EV_LEFT;
        }

        if (key == 3) {
            ev = EV_ENTER;
        }
        if (key == 2) {
            ev = EV_UP;
        }
        if (key == 1) {
            ev = EV_DOWN;
        }
    }

    serial_command = serialRead();

    if (serial_command == 'a' || serial_command == 'A') {
        ev = EV_LEFT;
    } else if (serial_command == 'd' || serial_command == 'D') {
        ev = EV_RIGHT;
    } else if (serial_command == 's' || serial_command == 'S') {
        ev = EV_DOWN;
    } else if (serial_command == 'w' || serial_command == 'W') {
        ev = EV_UP;
    } else if (serial_command == 'f' || serial_command == 'F') {
        ev = EV_ENTER;
    } else {
        if (serial_command == '/') {
            memset(protocolo, 0, SIZE);
            protocolo[0] = serial_command;
            protocolo_index = 0;
        } else if (serial_command == ';') {
            protocolo[protocolo_index + 1] = serial_command;
            processarProtocolo();
            protocolo_index = 0;
            memset(protocolo, 0, SIZE);
        } else if (protocolo_index == SIZE) {
            memset(protocolo, 0, SIZE);
            protocolo_index = 0;
        } else if (serial_command) {
            protocolo_index++;
            protocolo[protocolo_index] = serial_command;
            serialString(protocolo);
        }
    }



    key_ant = key;
    return ev;
}

void processarProtocolo() {
    //PROTOCOLO SENSORES
    //CH -> change
    //M1 -> meter 1 | Sensor 1
    //M2 -> meter 2 | Sensor 2
    //: -> proxima instrução
    //HV -> valor alto
    //LV -> valor baixo
    //: -> proxima instrução
    //valor do alarme -> 4 digitos
    //min 0 | max 100;

    //PROTOCOLO LINGUAGEM
    //CH -> change
    //LG -> language | linguagem
    //: -> proxima instrucao
    //valor da linguagem
    // 0 | PT 
    // 1 | EN

    unsigned int err = 0;

    if ((protocolo[1] == 'C' || protocolo[1] == 'c') || (protocolo[2] == 'H' || protocolo[2] == 'h')) {
        if (protocolo[3] == 'M' || protocolo[3] == 'm') {
            int new_value = 0;
            if (protocolo[4] == '1') {
                if ((protocolo[6] == 'L' || protocolo[6] == 'l') && (protocolo[7] == 'V' || protocolo[7] == 'v')) {
                    for (int i = 9; i <= protocolo_index; i++) {
                        if (new_value != 0) {
                            new_value *= 10;
                        }
                        if (protocolo[i] >= '0' && protocolo[i] <= '9') {
                            new_value += (protocolo[i] - '0');
                        } else {
                            serialString("Error: invalid alarm value | Erro: valor invalido de alarme");
                            return;
                        }
                    }
                    if (new_value != 0) {
                        if (new_value > 100) {
                            new_value = 100;
                        }
                        setAlarmLevel(0, 1, new_value);
                    } else {
                        serialString("Error: invalid alarm value | Erro: valor invalido de alarme");
                    }
                } else if ((protocolo[6] == 'H' || protocolo[6] == 'h') && (protocolo[7] == 'V' || protocolo[7] == 'v')) {
                    for (int i = 9; i <= protocolo_index; i++) {
                        if (new_value != 0) {
                            new_value *= 10;
                        }
                        if (protocolo[i] >= '0' && protocolo[i] <= '9') {
                            new_value += (protocolo[i] - '0');
                        } else {
                            serialString("Error: invalid alarm value | Erro: valor invalido de alarme");
                            return;
                        }
                    }
                    if (new_value != 0) {
                        if (new_value > 100) {
                            new_value = 100;
                        }
                        setAlarmLevel(0, 0, new_value);
                    } else {
                        serialString("Error: invalid alarm value | Erro: valor invalido de alarme");
                    }
                } else {
                    err = 1;
                }
            } else if (protocolo[4] == '2') {
                if ((protocolo[6] == 'L' || protocolo[6] == 'l') && (protocolo[7] == 'V' || protocolo[7] == 'v')) {
                    for (int i = 9; i <= protocolo_index; i++) {
                        if (new_value != 0) {
                            new_value *= 10;
                        }
                        if (protocolo[i] >= '0' && protocolo[i] <= '9') {
                            new_value += (protocolo[i] - '0');
                        } else {
                            serialString("Error: invalid alarm value | Erro: valor invalido de alarme");
                            return;
                        }
                    }

                    if (new_value != 0) {
                        if (new_value > 100) {
                            new_value = 100;
                        }
                        setAlarmLevel(1, 1, new_value);
                    } else {
                        serialString("Error: invalid alarm value | Erro: valor invalido de alarme");
                    }

                } else if ((protocolo[6] == 'H' || protocolo[6] == 'h') && (protocolo[7] == 'V' || protocolo[7] == 'v')) {
                    for (int i = 9; i <= protocolo_index; i++) {
                        if (new_value != 0) {
                            new_value *= 10;
                        }
                        if (protocolo[i] >= '0' && protocolo[i] <= '9') {
                            new_value += (protocolo[i] - '0');
                        } else {
                            serialString("Error: invalid alarm value | Erro: valor invalido de alarme");
                            return;
                        }
                    }
                    if (new_value != 0) {
                        if (new_value > 100) {
                            new_value = 100;
                        }
                        setAlarmLevel(1, 0, new_value);
                    } else {
                        serialString("Error: invalid alarm value | Erro: valor invalido de alarme");
                    }
                } else {
                    err = 1;
                }
            } else {
                err = 1;
            }
        } else if ((protocolo[3] == 'L' || protocolo[3] == 'l') && (protocolo[4] == 'G' || protocolo[4] == 'g')) {
            if (protocolo[6] == '0' || ((protocolo[6] == 'P' || protocolo[7] == 'p') && (protocolo[7] == 'T' || protocolo[7] == 't'))) {
                setLanguage(0);
            } else if (protocolo[6] == '1' || ((protocolo[6] == 'E' || protocolo[6] == 'e') && (protocolo[7] == 'N' || protocolo[7] == 'n'))) {
                setLanguage(1);
            }
        } else {
            err = 1;
        }
    } else {
        err = 1;
    }

    if (err == 1) {
        serialString("Error: invalid protocol | Erro: protocolo invalido");
    }
}