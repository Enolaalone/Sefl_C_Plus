#include "reg52.h" 
sbit HC138_C=P2^7;
sbit HC138_B=P2^6;
sbit HC138_A=P2^5;

unsigned char Table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};

void HC138(unsigned int n){
	switch(n){
		case 6:
			HC138_C=1;
			HC138_B=1;
			HC138_A=0;
			break;
		case 7:
			HC138_C=1;
			HC138_B=1;
			HC138_A=1;
			break;
	}
}


void Delay(unsigned int t){
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


void Tube(unsigned int n,unsigned char w){
	HC138(6);
	P0=w;
	HC138(7);
	P0=Table[n];
	Delay(1);
}


int main(){
	unsigned int i,j,n=0,k;
	unsigned char l,m;
	for(;n<99999999;n++){

		for(j=0;j<10;j++){
			k=n;
			m=0x80;
			while(m!=0x00){
				l=k%10;
				if((l|k)!=0||m==0x80)Tube(l,m);
				else Delay(1);
				k/=10;
				m>>=1;
			}
		}
	}
}
