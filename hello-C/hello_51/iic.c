#include <reg52.h>
#include <intrins.h>

sbit sda = P0^1;
sbit scl = P0^2;

void Delay10ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 18;
	j = 235;
	do
	{
		while (--j);
	} while (--i);
}


void i2c_start(){
	scl = 1;
	sda = 1;
	Delay10ms();  // 延时大于4us
	sda = 0;
	Delay10ms();  //低电平也大于4us
}

void i2c_stop(){
	scl = 1;
	sda = 0;
	Delay10ms();  //低电平大于10ms
	sda = 1;
	Delay10ms();  //高电平大于10ms
}

void i2c_ack(){
	scl = 0;
	sda = 0;  //先让sda变为低电平
	Delay10ms();  //保证scl高电平时sda为 低 电平
	scl = 1;
	Delay10ms();
	scl = 0;
	Delay10ms();  
}

void i2c_nack(){
	scl = 0;
	sda = 1;  //先让sda变为高电平
	Delay10ms();  //保证scl高电平时sda为 高 电平
	scl = 1;
	Delay10ms();
	scl = 0;
	Delay10ms();  
}

unsigned char i2c_wait_ack(){
  unsigned char ack_level;
	sda = 1; //数据总线空闲
	scl = 0;
	Delay10ms();
	scl = 1;
	Delay10ms();
	ack_level = sda; //sda = 0,ack; sda = 1, nack
	scl = 0;
	Delay10ms();
	return ack_level;
}

unsigned char byteMSB(unsigned char wdata){
	return (wdata & 0x80)>>7;
} 

void i2c_write_byte(unsigned char wdata){  //先写最高位
  int i;
	for(i = 0; i < 8;i++){
		scl = 0;  //发送前scl为低电平
	  Delay10ms();
		if(byteMSB(wdata)) sda = 1;  //最高位为1，输出高电平，否则输出低电平
		//if(wdata & 0x80) sda = 1;
		else sda = 0;
		scl = 1;  //数据准备好就拉高写入
		Delay10ms();
		wdata <<= 1; //左移一位，下一步提取第二高位
	}
}

unsigned char i2c_read_byte(){  //先读最高位
	unsigned char value = 0;
	int i;
	sda = 1; //释放总线
	for(i=0;i<8;i++){
		scl = 0;
	  Delay10ms();
	  scl = 1;
	  Delay10ms(); //等待数据稳定再读取
	  if(sda == 1){
		  value = value | 0x01;  //读取到的数据放在最低位
	  }
		value <<= 1; //空出最低位
	}
	return value;
}

void main(){
	i2c_start();
	i2c_write_byte(0x55);
	i2c_ack();
	i2c_stop();
	while(1){}
}