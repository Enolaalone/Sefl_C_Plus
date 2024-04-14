#include "reg52.h"
sfr P4=0xc0;//定义P4端口；
//sbit R1=P3^0;
//sbit R2=P3^1;
//sbit R3=P3^2;
//sbit R4=P3^3;

sbit C1=P4^4;
sbit C2=P4^2;
sbit C3=P3^5;
sbit C4=P3^4;

unsigned char key_num;
void switch_LED(unsigned char c){
	P2=(P2&0x1f)|0x80;//选中LED YC4
	P0=c;
}

void switch_R(unsigned char R){//R赋值,扫描
	switch (R){
		case 1:
			P3=(P3&0xf0)| 0x0e;
			break;
		case 2:
			P3=(P3&0xf0)| 0x0d;
			break;
		case 3:
			P3=(P3&0xf0)| 0x0b;
			break;
		case 4:
			P3=(P3&0xf0)| 0x07;
			break;
	}
}

void chack_C(){
	C1=C2=C3=C4=1;
}

void scanLED(){
//------第一行
	switch_R(1);
	chack_C();
	if(C1==0){
		//while(C1==0);
		switch_LED(0xfe);
	}
	else if(C2==0){
		//while(C2==0);
		switch_LED(0xfd);
	}
	else if(C3==0){
		//while(C3==0);
		switch_LED(0xfb);
	}
	else if(C4==0){
		//while(C4==0);
		switch_LED(0xf7);
	}
//第2行
	switch_R(2);
	chack_C();
	if(C1==0||C2==0||C3==0||C4==0){
		//while(C1==0||C2==0||C3==0||C4==0);
		switch_LED(0xff);
	}

//第3行
	switch_R(3);
	chack_C();
	if(C1==0){
		//while(C1==0);
		switch_LED(0xef);
	}
	else if(C2==0){
		//while(C2==0);
		switch_LED(0xdf);
	}
	else if(C3==0){
		//while(C3==0);
		switch_LED(0xbf);
	}
	else if(C4==0){
		//while(C4==0);
		switch_LED(0x7f);
	}

//第4行
	switch_R(4);
	chack_C();
	if(C1==0||C2==0||C3==0||C4==0){
		//while(C1==0||C2==0||C3==0||C4==0);
		switch_LED(0xff);
	}


}

void main(){
	switch_LED(0xff);
	while(1){
		scanLED();

	}
}