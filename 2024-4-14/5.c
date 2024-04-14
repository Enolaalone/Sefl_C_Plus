#include "reg52.h"


unsigned char c=0x00;
unsigned char pre_c=0x00;
unsigned char ppre_c=0x00;
char ss7=-1;
//独立按键
sbit S7=P3^0;
sbit S6=P3^1;
sbit S5=P3^2;
sbit S4=P3^3;

void delay(unsigned int t){
	unsigned int tmp;
	tmp=60*t;
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

void InitTimer3(){
	TMOD= 0x10;
	TH1=(65535-50000)/256;//10ms
	TL1=(65535-50000)%256;
	ET1=1;
	EA=1;
	TR1=1;
}

void switch_lit(){
		P2=(P2&0x1f)|0x80;//YC4
	if(pre_c!=c)return;
		P0=~c;
}

void lit(){
		P2=(P2&0x1f)|0x80;//YC4

		P0=~c;
		delay(200);
}
void lit_pp(){
		P2=(P2&0x1f)|0x80;//YC4

		P0=~ppre_c;
		delay(200);
		P0=0xff;
		delay(200);
		P0=~ppre_c;
		delay(200);
		P0=0xff;
		delay(200);
		P0=~ppre_c;
		delay(200);
		P0=0xff;
		delay(200);
}
unsigned int count=0;
void INTO3() interrupt 3//定时函数
{
	pre_c=c;
	TH1=(65535-50000)/256;
	TL1=(65535-50000)%256;
	if(!S6&&c==0x00){//按下
		delay(10);
		if(!S6){
			if(ppre_c!=0x00)
			c=ppre_c;
			else c=0x01;
		}
	}
	if(!S5&&c!=0x00){//按下
		delay(10);
		if(!S5){
			ppre_c=c;
			c=0x00;
		}
	}

	if(!S7&&c!=0x00&&ss7==-1){
		delay(10);
		if(!S7){
			ss7=1;
		}
	}

	if(ss7==1){
		count++;

		if(count>=40){
			while(!S7){
				c<<=1;
				if(c==0x00)c=0x01;
				lit();
			}	
			c>>=1;
		}
	}
	
	if(S7&&ss7==1){
		if(count<100){
			c<<=1;
			if(c==0x00)c=0x01;
			delay(200);
		}
		ss7=-1;
		count=0;
	}
}


void main(){
	InitTimer3();
	while(1){
		switch_lit();
	}
}
