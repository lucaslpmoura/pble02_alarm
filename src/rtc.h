#ifndef RTC_h
#define RTC_h

//definição dos endereços
#define SEC     0x00
#define MIN     0x01
#define HOUR    0x02
#define WEEKDAY 0x03
#define DAY     0x04
#define MONTH   0x05
#define YEAR    0x06

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
#endif
