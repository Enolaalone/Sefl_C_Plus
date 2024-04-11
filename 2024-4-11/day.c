#include "reg52.h"  
#include "math.h"

sbit HC_C=P2^7;
sbit HC_B=P2^6;
sbit HC_A=P2^5;

unsigned int Table[19]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e,0xbf,0x7f,0xff};//0-9,A-F,-,.,off
void HC138(unsigned int n){
	switch (n){
		case 6:
			HC_C=1;
			HC_B=1;
			HC_A=0;
			break;
		case 7:
			HC_C=1;
			HC_B=1;
			HC_A=1;
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




void lit(unsigned char w,unsigned int n){
	HC138(6);
	P0=w;
	HC138(7);
	P0=Table[n];
	delay(2);
}



void num_show(unsigned int year,unsigned int month,unsigned int day){
	unsigned int i,j;
	
	for(i=0;i<20;i++){
		for(j=0;j<10;j++){
			if(j<4)
				lit(0x01<<j,(year/((int)pow(10,3-j)))%10);
			else if(j==4)
				lit(0x01<<j,(month/10)%10);
			else if(j==5)
				lit(0x01<<j,month%10);
			else if(j==6)
				lit(0x01<<j,(day/10)%10);
			else if(j==7)
				lit(0x01<<j,day%10);
			else if(j==8)
				lit(0x01<<3,17);
			else lit(0x01<<5,17);
		}
	}
	lit(0xff,18);
	delay(300);
}


void main(){
	while(1){
		num_show(2023,4,11);

	}


}