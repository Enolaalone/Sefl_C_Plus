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

unsigned char c;
void INTO(){
		IT0=1;
		EX0=1;
		EA=1;
}

void ServiceINTO() interrupt 0
{
P2=(P2&0x1f)|0x80;
P0=0x00;
	//	if(C1==0&&R1==0)c=1;
	//else if(C2==0&&R1==0)c=2;
	//else if(C3==0&&R1==0)c=3;
	//else if(C4==0&&R1==0)c=4;
	//else if(C1==0&&R2==0)c=5;
	//else if(C2==0&&R2==0)c=6;
	//else if(C3==0&&R2==0)c=7;
	//else if(C4==0&&R2==0)c=8;
	//else if(C1==0&&R3==0)c=9;
	//else if(C2==0&&R3==0)c=10;
	//else if(C3==0&&R3==0)c=11;
	//else if(C4==0&&R3==0)c=12;
	//else if(C1==0&&R4==0)c=13;
	//else if(C2==0&&R4==0)c=14;
	//else if(C3==0&&R4==0)c=15;
	//else if(C4==0&&R4==0)c=16;
	
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

void switch_LED(){
	P2=(P2&0x1f)|0x80;//ѡ��LED YC4
}


void lit1(){//��˸
	switch_LED();
	P0=0x00;
	delay(500);
	P0=0xff;
	delay(500);
}

void lit2(){//��˫
	switch_LED();
	P0=0xaa;
	delay(500);
	P0=0xff;
	delay(500);
	P0=0x55;
	delay(500);
	P0=0xff;
	delay(500);
}

void lit3(){//sos
	unsigned int i;
	switch_LED();
	for(i=0;i<3;i++){
		P0=0xaa;
		delay(200);
		P0=0xff;
		delay(200);
	}
	for(i=0;i<3;i++){
		P0=0x55;
		delay(600);
		P0=0xff;
		delay(600);
	}
	for(i=0;i<3;i++){
		P0=0xaa;
		delay(200);
		P0=0xff;
		delay(200);
	}
}

void lit4(){//������
	unsigned int i;
	switch_LED();
	for(i=0;i<8;i++){
		P0=~(0x01<<i);
		delay(300);
	}
}

void lit5(){//������
	unsigned int i;
	switch_LED();
	for(i=0;i<8;i++){
		P0=~(0x80>>i);
		delay(300);
	}
}

void lit6(){//��������
	unsigned int i;
	switch_LED();
	for(i=0;i<8;i++){
		P0=~(0x01<<i);
		delay(200);
	}
	for(i=0;i<8;i++){
		P0=~(0x80>>i);
		delay(200);
	}
}

void lit7(){//����ˮ
	unsigned int i;
	unsigned char c;
	switch_LED();
  c=0;
	for(i=0;i<8;i++){
		c<<=1;
		P0=~(c|=0x01);
		delay(100);
	}
	for(i=0;i<8;i++){
		c<<=1;
		P0=~c;
		delay(100);
	}
}

void lit8(){//����ˮ
	unsigned int i;
	unsigned char c;
	switch_LED();
  c=0;
	for(i=0;i<8;i++){
		c>>=1;
		P0=~(c|=0x80);
		delay(100);
	}
	for(i=0;i<8;i++){
		c>>=1;
		P0=~c;
		delay(100);
	}
}

void lit9(){//������ˮ
	unsigned int i;
	unsigned char c;
	switch_LED();
  c=0;
	for(i=0;i<8;i++){
		c<<=1;
		P0=~(c|=0x01);
		delay(100);
	}
	for(i=0;i<8;i++){
		c<<=1;
		P0=~c;
		delay(100);
	}
	  c=0;
	for(i=0;i<8;i++){
		c>>=1;
		P0=~(c|=0x80);
		delay(100);
	}
	for(i=0;i<8;i++){
		c>>=1;
		P0=~c;
		delay(100);
	}
}

void lit10(){//������
	unsigned int i;
	switch_LED();
	for(i=0;i<200;i++){
		P0=0xff;
		delay(10-i/20);
		P0=0x00;
		delay(i/20);
	}
	delay(50);
	for(i=0;i<200;i++){
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
		P0=0xaa;
		delay(i/10);
	}
	delay(50);
	for(i=0;i<100;i++){
		P0=0xaa;
		delay(10-i/10);
		P0=0xff;
		delay(i/10);
	}
	delay(50);

	for(i=0;i<100;i++){
		P0=0xff;
		delay(10-i/10);
		P0=0x55;
		delay(i/10);
	}
	delay(50);
	for(i=0;i<100;i++){
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
		P0=c;
		delay(300);
	}
}


void lit15(){//������&����
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
			P0=c;
			delay(i/10);
		}
		delay(20);
		for(i=0;i<100;i++){
			P0=c;
			delay(10-i/10);
			P0=0xff;
			delay(i/10);
		}
		delay(10);
	}
}

void lit16(){//������&����
	unsigned int i,j;
	unsigned char c;
	switch_LED();
	c=0xff;
	for(j=0;j<8;j++){
		c<<=1;

		for(i=0;i<100;i++){
			P0=0xff;
			delay(10-i/10);
			P0=c;
			delay(i/10);
		}
		delay(20);
		for(i=0;i<100;i++){
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
			P0=c;
			delay(i/10);
		}
		delay(20);
		for(i=0;i<100;i++){
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


	switch(c){
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


void main(){
	unsigned int i;
	c=0;
	INTO();
	switch_LED();
	P0=0xff;
delay(1000);
	while(1){
		//for(i=0;i<4;i++){
			//switch_RC(i);
			//switch_lit();
		//}
	}
}