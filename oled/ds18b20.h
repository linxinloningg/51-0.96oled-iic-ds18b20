#ifndef __DS18B20_H
#define __DS18B20_H
extern unsigned char temperature;
extern unsigned char value;
void Delay(unsigned long t);
void Init_DS18B20(void);
unsigned char ReadOneChar(void);
void WriteOneChar(unsigned char dat);
void ReadTemperature(void);
#endif