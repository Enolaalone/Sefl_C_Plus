#include "reg52.h"

sbit HC_C=P2^7;
sbit HC_B=P2^6;
sbit HC_A=P2^5;

unsigned char Table[16]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};//0-9,A-F
void HC_138(int n){
	switch(n){
	case 7:
		HC_C=1;
		HC_B=1;
		HC_A=1;
		break;
	case 6:
		HC_C=1;
		HC_B=1;
		HC_A=0;
		break;
	case 4:
		HC_C=1;
		HC_B=0;
		HC_A=0;
		break;
	}
}

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

void lit(unsigned char n,unsigned int num){
	HC_138(6);
	P0=n;
	HC_138(7);
	P0=Table[num];
	delay(200);
}

void lit_tube(){
	unsigned int i,j;
	for(i=0;i<9;i++){
		if(i!=8)
		for(j=0;j<16;j++){
			lit(0x80>>i,j);
		}
		else
		for(j=0;j<16;j++){
			lit(0xff,j);
		}
	}
}

void main(){
	while(1){
		lit_tube();
		//HC_138(4);
		//P0=0x00;
		//delay(1000);
		//P0=0xff;
		//delay(1000);
	}

}

