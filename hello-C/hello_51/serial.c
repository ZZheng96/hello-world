#include <reg52.h>

void UARTinit(){
		//配置串口模式 1
	  SM0 = 0;
	  SM1 = 1;
	  //SCON = 0x40;
	  //配置计时器1为模式2
	  TMOD &= 0x0F;
	  TMOD |= 0x20;
	  //设置预装载值
	  TL1 = 0xFD;
	  TH1 = 0xFD;
	  //开始计数
	  TR1 = 1;
	  //设置SMOD=0；
	  PCON |= 0x00;
}

void main(){
	  UARTinit();
	  SBUF = 0x30; 
	  while(1){
		}
}