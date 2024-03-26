#include "reg52.h"

sbit HC138_A = P2^5;
sbit HC138_B = P2^6;
sbit HC138_C = P2^7;

void Delay(unsigned int t)
{
	while(t--);		//重复多次以得到较大的延时
	while(t--);
	while(t--);
	while(t--);	
	while(t--);
	while(t--);
	while(t--);
	while(t--);
}

void InstHC138(unsigned int n){//138锁存器切换函数
	switch(n){
		case 4:
			HC138_C=1;
			HC138_B=0;
			HC138_A=0;
			break;
		case 5:
			HC138_C=1;
			HC138_B=0;
			HC138_A=1;
			break;
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

void InstSystem(){
	HC138_C=1;
	HC138_B=0;
	HC138_A=1;
	P0=0x00;

}
void LED(){
	unsigned int i;
//控制灯
	InstHC138(4);
	for(i=0;i<3;i++){//亮灭3次
		P0=0x00;
		Delay(60000);
		P0=0xff;
		Delay(60000);
	}
	InstHC138(5);
	P0=0x10;//鸣叫
	Delay(60000);
	P0=0x00; 

	InstHC138(4);
	
	for(i=1;i<=8;i++){
		P0=0xff<<i;//从L1到L8依次点亮，低位控制低数值端口
		Delay(60000);

	}
		for(i=1;i<=8;i++){
		P0=~(0xff<<i);//从L1到L8依次点亮，低位控制低数值端口
		Delay(60000);

	}
	

}


void main()
{
	InstSystem();
	while(1)
	{
	 LED();
	}


}