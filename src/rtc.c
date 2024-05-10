#include "i2c.h"
#include "rtc.h"

//endereço do dispositivo, deslocado por causa do bit de RW
#define I2C_WRITE 0xde
#define I2C_READ  0xdf

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
	dsWriteData(0x7f & 0,SEC);
    dsWriteData(0,MIN);
    dsWriteData(0,HOUR);

	return;
}
void dsWriteData(unsigned char value, int address) {
	i2cWriteByte(1,0, I2C_WRITE);
	i2cWriteByte(0,0,address);
	i2cWriteByte(0,1,value);
    for(float i; i<100;i++);
}
int dsReadData(int address) {
	int result;
	i2cWriteByte(1,0,I2C_WRITE);
	i2cWriteByte(0,0,address);
	i2cWriteByte(1,0, I2C_READ);
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