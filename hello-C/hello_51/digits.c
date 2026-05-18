//#include <reg52.h>

//unsigned char table[]={
//0x3f,0x06,0x5b,0x4f,
//0x66,0x6d,0x7d,0x07,
//0x7f,0x6f
//};

//unsigned char num;

////延时函数
//void delay_ms(unsigned int xms)   //@12MHz
//{
//    unsigned int i, j;
//    for(i=xms;i>0;i--)
//    {
//        for(j=124;j>0;j--)
//        {}
//    }
//}

//void main()
//{
//    while(1)
//    {        
//        for(num=0;num<10;num++)
//        {
//           P2=table[num];
//           delay_ms(500);        
//        }
//    }
//}

//====================================================
//with two 74hc595 to manage IO

#include <reg52.h>

sbit ds = P0^3; //serial data input
sbit stcp = P0^4; //storage clock pulse
sbit shcp = P0^5; //shift clock pulse

unsigned char table[]={ // numbers to be sent
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f
};

void hc595_send_byte(unsigned char sbyte){
	int i;
	for(i=0;i<8;i++){
	  ds = sbyte >> 7 & 1; //exrtact the highest bit
		shcp = 0;
		shcp = 1;
		sbyte <<= 1; 
	}
}

void hc595_send_data(int num, int addr){
	hc595_send_byte(table[num]);
	hc595_send_byte(addr ? 0xFD : 0xFE);
	stcp = 0; //store and output code at the same time
	stcp = 1;
}

void main(){
	int i,j,k;
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			k=1190;  //timer around 1000ms
			while(k--){
				hc595_send_data(i,0);
			  hc595_send_data(j,1);
			}
		}
	}
}






