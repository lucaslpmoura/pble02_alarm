# 1 "rtc.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files/Microchip/MPLABX/v6.05/packs/Microchip/PIC18Fxxxx_DFP/1.3.36/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "rtc.c" 2
# 1 "./i2c.h" 1




 void i2cInit(void);
 unsigned char i2cWriteByte(unsigned char send_start, unsigned char send_stop, unsigned char byte);
 unsigned char i2cReadByte(unsigned char nack, unsigned char send_stop);
# 2 "rtc.c" 2
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
# 3 "rtc.c" 2





int dec2bcd(int value) {
 return ((value / 10 * 16) + (value % 10));
}
int bcd2dec(int value) {
 return ((value / 16 * 10) + (value % 16));
}
void dsInit(void) {
 i2cInit();
}
void dsStartClock(void) {
 dsWriteData(0x7f & 0,0x00);
    dsWriteData(0,0x01);
    dsWriteData(0,0x02);

 return;
}
void dsWriteData(unsigned char value, int address) {
 i2cWriteByte(1,0, 0xde);
 i2cWriteByte(0,0,address);
 i2cWriteByte(0,1,value);
    for(float i; i<100;i++);
}
int dsReadData(int address) {
 int result;
 i2cWriteByte(1,0,0xde);
 i2cWriteByte(0,0,address);
 i2cWriteByte(1,0, 0xdf);
 result = i2cReadByte(1,1 );
 return result;
}
void setHours(int hours){
    int mod = hours % 24;
    char byte;
    byte = mod/10;
    byte<<=4;
    byte+=mod%10;

    i2cWriteByte(1, 0, 0xde);
    i2cWriteByte(0, 0, 0x02);
    i2cWriteByte(0, 1, byte);
}

void setMinutes(int minutes){
    int mod = minutes % 60;
    char byte;
    byte = mod/10;
    byte<<=4;
    byte+=mod%10;

    i2cWriteByte(1, 0, 0xde);
    i2cWriteByte(0, 0, 0x01);
    i2cWriteByte(0, 1, byte);
}

void setSeconds(int seconds){
    int mod = seconds % 60;
    char byte;
    byte = mod/10;
    byte<<=4;
    byte+=mod%10;

    i2cWriteByte(1, 0, 0xde);
    i2cWriteByte(0, 0, 0x00);
    i2cWriteByte(0, 1, byte);
}

int getHours(){
    i2cWriteByte(1, 0, 0xde);
    i2cWriteByte(0, 0, 0x02);
    i2cWriteByte(1, 0, 0xdf);
    char h = i2cReadByte(1,1);

    return bcd2dec(h);
}

int getMinutes(){
    i2cWriteByte(1, 0, 0xde);
    i2cWriteByte(0, 0, 0x01);
    i2cWriteByte(1, 0, 0xdf);
    char h = i2cReadByte(1,1);

    return bcd2dec(h);
}

int getSeconds(){
    i2cWriteByte(1, 0, 0xde);
    i2cWriteByte(0, 0, 0x00);
    i2cWriteByte(1, 0, 0xdf);
    char h = i2cReadByte(1,1);

    return bcd2dec(h);
}
