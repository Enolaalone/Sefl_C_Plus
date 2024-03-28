#include <reg52.h>

sbit HC138_C=P2^7;
sbit HC138_B=P2^6;
sbit HC138_A=P2^5;

void delay(unsigned int t)//ÑÓÊ±º¯Êý1000=1s
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

void breath(){
	unsigned int i;
	for(i=0;i<200;i++){
		P0=0x00;
		delay(i/20);
		P0=0xff;
		delay(10-i/20);
		
		}
	delay(20);
	for(i=0;i<200;i++){
		P0=0xff;
		delay(i/20);
		P0=0x00;
		delay(10-i/20);
		
		}
	delay(10);
}
int main(){
	HC138_C=1;
	HC138_B=0;
	HC138_A=0;
	while(1){
		breath();
	}
}