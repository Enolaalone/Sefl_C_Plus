#include "reg52.h"

sbit HC138_A = P2^5;
sbit HC138_B = P2^6;
sbit HC138_C = P2^7;

void delay(unsigned int t)//延时函数1000=1s
{
	unsigned int tmp;
	t*=60;
	tmp=t;

	while(t--);	
	t=tmp;
	while(t--);	
	t=tmp;
	while(t--);	
	t=tmp;
	while(t--);	
	t=tmp;
	while(t--);	
	t=tmp;
	while(t--);	
	t=tmp;
	while(t--);	
	t=tmp;
	while(t--);	
	t=tmp;
	while(t--);	
	t=tmp;
	while(t--);	
	t=tmp;
}

void breath(unsigned n){
	unsigned int i;
	for(i=0;i<30;i++){
		P0=n;
		delay(i/3);
		P0=0xff;
		delay(10-i/3);
		
		}
	delay(20);
	for(i=0;i<30;i++){
		P0=0xff;
		delay(i/3);
		P0=n;
		delay(10-i/3);
		
		}
	delay(100);
}

void Ledriver()
{
  int c;
	//unsigned int num;
	unsigned char i;
	HC138_C = 1;	//选中138的Y4，用以控制8个LED灯
	HC138_B = 0;
	HC138_A = 0;

	
	for (i=0;i<8;i++)
	{
		c=1;
		//P0=0xff^(c<<i);
		breath(0xff^(c<<i));
		//delay(1000);
	}

	for (i=0;i<8;i++)
	{
		c=0x80;
		//P0=0xff^(c>>i);
		breath(0xff^(c>>i));
		//delay(1000);
	}	
}



void main()
{

	while(1)
	{
	Ledriver();
	}


}