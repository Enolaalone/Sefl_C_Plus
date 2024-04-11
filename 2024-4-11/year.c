#include "reg52.h"  
#include "math.h"

sbit HC_C=P2^7;
sbit HC_B=P2^6;
sbit HC_A=P2^5;

unsigned int Table[17]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e,0xbf};//0-9,A-F,-
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



void num_show(unsigned int year,unsigned int month){
	unsigned int i,j;
	
	for(i=0;i<20;i++){
		for(j=0;j<8;j++){
			if(j<4)
				lit(0x01<<j,(year/((int)pow(10,3-j)))%10);
			else if(j==4||j==5)
				lit(0x01<<j,16);
			else if(j==6)
				lit(0x01<<j,(month/10)%10);
			else lit(0x01<<j,month%10);
		}
	}
}


void main(){
	unsigned int month;
	while(1){
		for(month=1;month<13;month++)
		num_show(2023,month);

	}


}