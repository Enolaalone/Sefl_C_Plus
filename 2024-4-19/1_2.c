#include <reg52.h>

sfr P4=0xc0;//定义P4端口；
//sbit R1=P3^0;
//sbit R2=P3^1;
//sbit R3=P3^2;
//sbit R4=P3^3;

sbit C1=P4^4;
sbit C2=P4^2;
sbit C3=P3^5;
sbit C4=P3^4;

unsigned int i=1;
unsigned int k=8;
unsigned char LED[9]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f,0xff};
void switch_LED(unsigned char c){
	P2=(P2&0x1f)|0x80;//选中LED YC4
	P0=c;
}

void switch_RC(unsigned char R){//R赋值,扫描
	switch (R){
		case 1:
			P3=(P3&0xf0)| 0x0e;
			C1=C2=C3=C4=1;//C要放在P3 R赋值之后
			break;
		case 2:
			P3=(P3&0xf0)| 0x0d;
			C1=C2=C3=C4=1;
			break;
		case 3:
			P3=(P3&0xf0)| 0x0b;
			C1=C2=C3=C4=1;
			break;
		case 4:
			P3=(P3&0xf0)| 0x07;
			C1=C2=C3=C4=1;
			break;
	}
}


void scanLED(){
//------第i行
	switch_RC(i);
	if((!C1||!C2||!C3||!C4)&&!(i%2)){
			if((4*((i-1)/2)==k&&!C1)||(4*((i-1)/2)+1==k&&!C2)||(4*((i-1)/2)+2==k&&!C3)||(4*((i-1)/2)+3==k&&!C4))k=8;
			while(!C1||!C2||!C3||!C4)switch_LED(LED[k]);}
  else if(!C1){
			while(!C1){k=(i/2)*4;switch_LED(LED[k]);}
	}
	else if(C2==0){
			while(!C2){k=(i/2)*4+1;switch_LED(LED[k]);}
	}
	else if(C3==0){
			while(!C3){k=(i/2)*4+2;switch_LED(LED[k]);}
	}
	else if(C4==0){
			while(!C4){k=(i/2)*4+3;switch_LED(LED[k]);}
	}
	i=(i==4)?1:i+1;//循环递增
}

void main(){
	switch_LED(0xff);
	while(1){
		scanLED();
	}
}