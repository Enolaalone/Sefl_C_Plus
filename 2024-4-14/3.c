#include "reg52.h"
sfr P4=0xc0;//定义P4端口；
sbit R1=P3^0;
sbit R2=P3^1;
sbit R3=P3^2;
sbit R4=P3^3;

sbit C1=P4^4;
sbit C2=P4^2;
sbit C3=P3^5;
sbit C4=P3^4;

unsigned char key_num=0xff;
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
void InitTimer0(){
	TMOD = 0x01;//启用定时器0
	TH0=(65535-50000)/256;//计时器高八位
	TL0=(65535-50000)%256;//计时器低八位
	ET0=1;//计时器0开关
	EA=1;//中断总开关
	TR0=1;//启动
}
void switch_LED(unsigned char c){
	P2=(P2&0x1f)|0x80;//选中LED YC4
	P0=c;
	delay(1000);
}
void chack_C(){
	C1=C2=C3=C4=1;
}
void switch_R(unsigned char R){//R赋值,扫
	switch (R){
		case 1:
			P3=(P3&0xf0)| 0x0e;
			chack_C();
			break;
		case 2:
			P3=(P3&0xf0)| 0x0d;
			chack_C();
			break;
		case 3:
			P3=(P3&0xf0)| 0x0b;
			chack_C();
			break;
		case 4:
			P3=(P3&0xf0)| 0x07;
			chack_C();
			break;
	}
}


unsigned char n=0;
void scanLED() 
{
	TH0=(65535-50000)/256;//计时器高八位
	TL0=(65535-50000)%256;//计时器低八位
	n++;
	if(n==10){
		switch_LED(0xfe);
		delay(1000);
		n=0;
 }
}

void liy()interrupt 1
{
	unsigned int i;
	TH0=(65535-50000)/256;//计时器高八位
	TL0=(65535-50000)%256;//计时器低八位
	n++;
	//for(i=1;1<5;i++){
	//------第一行
	if(n==1){
		n=0;
		switch_R(1);
		if(C1==0&&R1==0){
			//while(C1==0);
			switch_LED(0xfe);
		}
		else if(C2==0&&R1==0){
			//while(C2==0);
			switch_LED(0xfd);
		}
		else if(C3==0&&R1==0){
			//while(C3==0);
			switch_LED(0xfb);
		}
		else if(C4==0&&R1==0){
			//while(C4==0);
			switch_LED(0xf7);
		}

	}

}
void main(){
	
	InitTimer0();
	while(1){
	switch_LED(0x7f);

	}


}