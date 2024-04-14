#include "reg52.h"
sfr P4=0xc0;

sbit R1=P3^0;
sbit R2=P3^1;
sbit R3=P3^2;
sbit R4=P3^3;

sbit C1=P4^4;
sbit C2=P4^2;
sbit C3=P3^5;
sbit C4=P3^4;

unsigned char num;
unsigned char pre_num;


void delay(unsigned int t){
	unsigned int tmp;
	tmp=60*t;
	while(t--);
if(pre_num!=num)return;
	t=tmp;
	while(t--);
if(pre_num!=num)return;
	t=tmp;
	while(t--);
if(pre_num!=num)return;
	t=tmp;
	while(t--);
if(pre_num!=num)return;
	t=tmp;
	while(t--);
if(pre_num!=num)return;
	t=tmp;
	while(t--);
if(pre_num!=num)return;
	t=tmp;
	while(t--);
if(pre_num!=num)return;
	t=tmp;
	while(t--);
if(pre_num!=num)return;
	t=tmp;
	while(t--);
if(pre_num!=num)return;
	t=tmp;
	//while(t--);
	//t=tmp;
}

void switch_LED(){
	P2=(P2&0x1f)|0x80;//选中LED YC4
}


void lit1(){//闪烁
	switch_LED();
if(pre_num!=num)return;
	P0=0x00;
	delay(300);
	P0=0xff;
	delay(300);
}

void lit2(){//单双
	switch_LED();
if(pre_num!=num)return;
	P0=0xaa;
	delay(300);
	P0=0xff;
	delay(300);
if(pre_num!=num)return;
	P0=0x55;
	delay(300);
	P0=0xff;
	delay(300);
}

void lit3(){//sos
	unsigned int i;
	switch_LED();
	for(i=0;i<3;i++){
if(pre_num!=num)return;
		P0=0xaa;
		delay(100);
		P0=0xff;
		delay(100);
	}
	for(i=0;i<3;i++){
if(pre_num!=num)return;
		P0=0x55;
		delay(300);
		P0=0xff;
		delay(300);
	}
	for(i=0;i<3;i++){
if(pre_num!=num)return;
		P0=0xaa;
		delay(100);
		P0=0xff;
		delay(100);
	}
}

void lit4(){//正跑马
	unsigned int i;
	switch_LED();
	for(i=0;i<8;i++){
if(pre_num!=num)return;
		P0=~(0x01<<i);
		delay(200);
	}
}

void lit5(){//逆跑马
	unsigned int i;
	switch_LED();
	for(i=0;i<8;i++){
if(pre_num!=num)return;
		P0=~(0x80>>i);
		delay(200);
	}
}

void lit6(){//正逆跑马
	unsigned int i;
	switch_LED();
	for(i=0;i<8;i++){
if(pre_num!=num)return;
		P0=~(0x01<<i);
		delay(200);
	}
	for(i=0;i<8;i++){
if(pre_num!=num)return;
		P0=~(0x80>>i);
		delay(200);
	}
}

void lit7(){//正流水
	unsigned int i;
	unsigned char c;
	switch_LED();
  c=0;
	for(i=0;i<8;i++){
		c<<=1;
if(pre_num!=num)return;
		P0=~(c|=0x01);
		delay(100);
	}
	for(i=0;i<8;i++){
		c<<=1;
if(pre_num!=num)return;
		P0=~c;
		delay(100);
	}
}

void lit8(){//逆流水
	unsigned int i;
	unsigned char c;
	switch_LED();
  c=0;
	for(i=0;i<8;i++){
		c>>=1;
if(pre_num!=num)return;
		P0=~(c|=0x80);
		delay(100);
	}
	for(i=0;i<8;i++){
		c>>=1;
if(pre_num!=num)return;
		P0=~c;
		delay(100);
	}
}

void lit9(){//正逆流水
	unsigned int i;
	unsigned char c;
	switch_LED();
  c=0;
	for(i=0;i<8;i++){
		c<<=1;
if(pre_num!=num)return;
		P0=~(c|=0x01);
		delay(100);
	}
	for(i=0;i<8;i++){
		c<<=1;
if(pre_num!=num)return;
		P0=~c;
		delay(100);
	}
	  c=0;
	for(i=0;i<8;i++){
		c>>=1;
if(pre_num!=num)return;
		P0=~(c|=0x80);
		delay(100);
	}
	for(i=0;i<8;i++){
		c>>=1;
if(pre_num!=num)return;
		P0=~c;
		delay(100);
	}
}

void lit10(){//呼吸灯
	unsigned int i;
	switch_LED();
	for(i=0;i<200;i++){
		P0=0xff;
		delay(10-i/20);
if(pre_num!=num)return;
		P0=0x00;
		delay(i/20);
	}
	delay(50);
	for(i=0;i<200;i++){
if(pre_num!=num)return;
		P0=0x00;
		delay(10-i/20);
		P0=0xff;
		delay(i/20);
	}
	delay(10);
}
void lit11(){
	unsigned int i;
	switch_LED();

	for(i=0;i<100;i++){
		P0=0xff;
		delay(10-i/10);
if(pre_num!=num)return;
		P0=0xaa;
		delay(i/10);
	}
	delay(50);
	for(i=0;i<100;i++){
if(pre_num!=num)return;
		P0=0xaa;
		delay(10-i/10);
		P0=0xff;
		delay(i/10);
	}
	delay(50);

	for(i=0;i<100;i++){
		P0=0xff;
		delay(10-i/10);
if(pre_num!=num)return;
		P0=0x55;
		delay(i/10);
	}
	delay(50);
	for(i=0;i<100;i++){
if(pre_num!=num)return;
		P0=0x55;
		delay(10-i/10);
		P0=0xff;
		delay(i/10);
	}
	delay(50);
}

void lit12(){//close
	int i,j;
	unsigned char c;
	switch_LED();

	for(i=3;i>=0;i--){
		c=0;
		for(j=0;j<2*i;j++){
			c<<=1;
			c|=0x01;
		}
		c<<=4-i;
if(pre_num!=num)return;
		P0=c;
		delay(100);
	}

	for(i=3;i>=0;i--){
		c=0;
		for(j=0;j<2*i;j++){
			c<<=1;
			c|=0x01;
		}
		c<<=4-i;
if(pre_num!=num)return;
		P0=~c;
		delay(100);
	}

}

void lit13(){//open
	int i,j;
	unsigned char c;
	switch_LED();

	for(i=4;i>=0;i--){
		c=0;
		for(j=0;j<8-2*i;j++){
			c<<=1;
			c|=0x01;
		}
		c<<=i;
if(pre_num!=num)return;
		P0=c;
		delay(300);
	}
}

void lit14(){
	int i,j;
	unsigned char c;
	switch_LED();

	for(i=3;i>=0;i--){
		c=0;
		for(j=0;j<2*i;j++){
			c<<=1;
			c|=0x01;
		}
		c<<=4-i;
if(pre_num!=num)return;
		P0=c;
		delay(300);
	}

	for(i=4;i>=0;i--){
		c=0;
		for(j=0;j<8-2*i;j++){
			c<<=1;
			c|=0x01;
		}
		c<<=i;
if(pre_num!=num)return;
		P0=c;
		delay(300);
	}
}


void lit15(){//呼吸灯&跑马
	unsigned int i,j;
	unsigned char c;
	switch_LED();

	for(j=0;j<8;j++){
		c=1;
		c<<=j;
		c=~c;
		for(i=0;i<100;i++){
			P0=0xff;
			delay(10-i/10);
if(pre_num!=num)return;
			P0=c;
			delay(i/10);
		}
		delay(20);
		for(i=0;i<100;i++){
if(pre_num!=num)return;
			P0=c;
			delay(10-i/10);
			P0=0xff;
			delay(i/10);
		}
		delay(10);
	}
}

void lit16(){//呼吸灯&跑马
	unsigned int i,j;
	unsigned char c;
	switch_LED();
	c=0xff;
	for(j=0;j<8;j++){
		c<<=1;

		for(i=0;i<100;i++){
			P0=0xff;
			delay(10-i/10);
if(pre_num!=num)return;
			P0=c;
			delay(i/10);
		}
		delay(20);
		for(i=0;i<100;i++){
if(pre_num!=num)return;
			P0=c;
			delay(10-i/10);
			P0=0xff;
			delay(i/10);
		}
		delay(10);
	}
	c=0;
	for(j=0;j<8;j++){
		c<<=1;
		c|=0x01;

		for(i=0;i<100;i++){
			P0=0xff;
			delay(10-i/10);
if(pre_num!=num)return;
			P0=c;
			delay(i/10);
		}
		delay(20);
		for(i=0;i<100;i++){
if(pre_num!=num)return;
			P0=c;
			delay(10-i/10);
			P0=0xff;
			delay(i/10);
		}
		delay(10);
	}
}


void switch_lit() 
{
	switch(num){
		case 0:
			break;
		case 1:
			lit1();
			break;
		case 2:
			lit2();
			break;
		case 3:
			lit3();
			break;
		case 4:
			lit4();
			break;
		case 5:
			lit5();
			break;
		case 6:
			lit6();
			break;
		case 7:
			lit7();
			break;
		case 8:
			lit8();
			break;
		case 9:
			lit9();
			break;
		case 10:
			lit10();
			break;
		case 11:
			lit11();
			break;
		case 12:
			lit12();
			break;
		case 13:
			lit13();
			break;
		case 14:
			lit14();
			break;
		case 15:
			lit15();
			break;
		case 16:
			lit16();
			break;
	}
}

void switch_C(){
	C1=C2=C3=C4=1;
}
void switch_RC(unsigned int n){
	switch(n){
		case 0:
			P3=(P3&0xf0)|0x0e;
			//R1=0;R2=R3=R4=1;
			switch_C();
			break;
		case 1:
			P3=(P3&0xf0)|0x0d;
			switch_C();
			break;
		case 2:
			P3=(P3&0xf0)|0x0b;
			switch_C();
			break;
		case 3:
			P3=(P3&0xf0)|0x07;
			switch_C();
			break;
	}
}

void InitTimer0(){
	TMOD = 0x01;//启用定时器0
	TH0=(65535-10000)/256;//计时器高八位
	TL0=(65535-10000)%256;//计时器低八位
	ET0=1;//计时器0开关
	EA=1;//中断总开关
	TR0=1;//启动
}

unsigned char k=0;
void ServiceINTO1() interrupt 1
{
	unsigned int i;
		TH0=(65535-5000)/256;//计时器高八位
		TL0=(65535-5000)%256;//计时器低八位
 k++;
	if(k==1){
		k=0;
	pre_num=num;
	for(i=0;i<4;i++){
		switch_RC(i);
		if(C1==0&&R1==0){num=1;}
		else if(C2==0&&R1==0){num=2;}
		else if(C3==0&&R1==0){num=3;}
		else if(C4==0&&R1==0){num=4;}
		else if(C1==0&&R2==0){num=5;}
		else if(C2==0&&R2==0){num=6;}
		else if(C3==0&&R2==0){num=7;}
		else if(C4==0&&R2==0){num=8;}
		else if(C1==0&&R3==0){num=9;}
		else if(C2==0&&R3==0){num=10;}
		else if(C3==0&&R3==0){num=11;}
		else if(C4==0&&R3==0){num=12;}
		else if(C1==0&&R4==0){num=13;}
		else if(C2==0&&R4==0){num=14;}
		else if(C3==0&&R4==0){num=15;}
		else if(C4==0&&R4==0){num=16;}
		}
		//switch_lit();
	}
}
void main(){
	pre_num=num=7;
	InitTimer0();
	while(1){
		switch_lit();
	}
	
}