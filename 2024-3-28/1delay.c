#include "reg52.h"
sbit HC138_A = P2^5;
sbit HC138_B = P2^6;
sbit HC138_C = P2^7;

void delay(unsigned int t)//��ʱ����1000=1s
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

void lit(){
	HC138_C = 1;	//ѡ��138��Y4�����Կ���8��LED��
	HC138_B = 0;
	HC138_A = 0;

	P0=0x00;
	delay(1000);
	P0=0xff;
	delay(1000);
}
int main(){
	
	while(1){
		lit();
	}

}