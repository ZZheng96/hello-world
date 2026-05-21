// #include <reg52.h>

// void UARTinit(){
// 		//配置串口模式 1
// 	  SM0 = 0;
// 	  SM1 = 1;
// 	  //SCON = 0x40;
// 	  //配置计时器1为模式2
// 	  TMOD &= 0x0F;
// 	  TMOD |= 0x20;
// 	  //设置预装载值
// 	  TL1 = 0xFD;
// 	  TH1 = 0xFD;
// 	  //开始计数
// 	  TR1 = 1;
// 	  //设置SMOD=0；
// 	  PCON |= 0x00;
// }

// void send_str(char str[]){
// 	int i = 0;
// 	while(str[i] != '\0'){
// 		SBUF = str[i];
// 		while(TI == 0);  //直到TI=1溢出
// 		TI = 0;  //回复
// 		i++;
// 	}
// }

// void main(){
// 	  UARTinit();
// 	  //SBUF = 0x30; 
// 	  send_str("Hello world!");
// 	  while(1){
// 		}
// }

#include <reg52.h>

//串口中断控制led亮灭

sbit led = P2^7;

void UARTInit(){
	SCON = 0x50; //设置串口模式1，允许接收REN=1
	//设置计时器
	TMOD &= 0x0F;
	TMOD |= 0x20;
	TL1 = 0xFD;
	TH1 = 0xFD;
	TR1 = 1; //开启计时
	//使能串行中断
	ES = 1;
	EA = 1;

}

void Uart_receive() interrupt 4{  //串行中断号为 4
  char rdata;
	if(RI == 1){
			RI = 0;
			rdata = SBUF;
			if(rdata == 'O') led = 0; //点亮led
			else if(rdata == 'C') led = 1; //熄灭
	}
}

void main(){
//	char rdata;
//	UARTInit();
//	while(1){
//		if(RI == 1){
//			RI = 0;
//			rdata = SBUF;
//			if(rdata == 'O') led = 0; //点亮led
//			else if(rdata == 'C') led = 1; //熄灭
//		}
//	}
	UARTInit();
	while(1){}

}