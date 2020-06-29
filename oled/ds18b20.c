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
unsigned char ReadOneChar(void)  			//�����������ȴӸ������͵�ƽ1us���ϣ���ʹ��������Ϊ�ߵ�ƽ���Ӷ��������ź�
{
	unsigned char i=0; 		//ÿ����������̵ĳ���ʱ��Ϊ60us������������֮�������1us���ϵĸߵ�ƽ�ָ���
	unsigned char dat=0; 
	for (i=8;i>0;i--) 		//һ���ֽ���8λ 
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
	unsigned char i=0; 		//�����ߴӸߵ�ƽ�����͵�ƽ������д��ʼ�źš�15us֮�ڽ�����д��λ�͵��������ϣ�
	for(i=8;i>0;i--) 		//��15~60us֮��������߽��в���������Ǹߵ�ƽ��д1����д0������ 
	{
		DQ=0; 				//�ڿ�ʼ��һ��д����ǰ������1us���ϵĸߵ�ƽ�ָ��ڡ� 
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