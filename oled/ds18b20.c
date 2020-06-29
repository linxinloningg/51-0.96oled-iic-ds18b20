#include "ds18b20.h"
#include "reg51.h"
sbit DQ=P3^6;
unsigned char temperature;
unsigned char value;
void Delay(unsigned long t)
{
	while(t--);
}
void Init_DS18B20(void) 
{
	DQ=1; 					
	delay(8); 				
	DQ=0; 					
	delay(80); 				
	DQ=1; 					
	delay(5);
	delay(20);  	
}
unsigned char ReadOneChar(void)  			//主机数据线先从高拉至低电平1us以上，再使数据线升为高电平，从而产生读信号
{
	unsigned char i=0; 		//每个读周期最短的持续时间为60us，各个读周期之间必须有1us以上的高电平恢复期
	unsigned char dat=0; 
	for (i=8;i>0;i--) 		//一个字节有8位 
	{
		DQ=1; 
		Delay(1); 
		DQ=0;
		dat>>=1; 
		DQ=1; 
		if(DQ) 
		dat|=0x80; 
		Delay(4);
	} 
	return(dat);
}
void WriteOneChar(unsigned char dat) 
{ 
	unsigned char i=0; 		//数据线从高电平拉至低电平，产生写起始信号。15us之内将所需写的位送到数据线上，
	for(i=8;i>0;i--) 		//在15~60us之间对数据线进行采样，如果是高电平就写1，低写0发生。 
	{
		DQ=0; 				//在开始另一个写周期前必须有1us以上的高电平恢复期。 
		DQ=dat&0x01; 
		delay(5); 
		DQ=1; 
		dat>>=1;
	} 
	delay(4);
}
void ReadTemperature(void) 
{
unsigned char a;
unsigned char b;
Init_DS18B20(); 
WriteOneChar(0xcc); 
WriteOneChar(0x44);
delay(125);
Init_DS18B20();
WriteOneChar(0xcc);
WriteOneChar(0xbe);
a=ReadOneChar();
b=ReadOneChar();
temperature=b;
temperature=a+(temperature<<8);
	if((temperature&0xf800)==0xf800)
	{
		temperature=(~temp)+1;
		value=temperature*(-0.0625);
	}
	else
	{
		value=temperature*0.0625;	
	}	
}