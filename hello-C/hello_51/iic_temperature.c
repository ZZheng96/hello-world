#include <reg52.h>
#include <intrins.h>
#include <stdio.h>

sbit sda = P0^1;
sbit scl = P0^2;

void uart_init() //9600bps@11.0592MHz
{
    PCON &= 0x7F; //波特率不倍速
    SCON = 0x50; //8位数据,可变波特率
    TMOD &= 0x0F; //清除定时器1模式位
    TMOD |= 0x20; //设定定时器1为8位自动重装方式
    TL1 = 0xFD; //设定定时初值
    TH1 = 0xFD; //设定定时器重装值
    ET1 = 0; //禁止定时器1中断
    TR1 = 1; //启动定时器1
}

/*
 **重写printf调用的putchar函数，重定向到串口输出
 **需要引入头文件<stdio.h>
 *****/
char putchar(char dat) {
    //输出重定向到串口
    SBUF = dat; //写入发送缓冲寄存器
    while (!TI); //等待发送完成，TI发送溢出标志位 置1
    TI = 0; //对溢出标志位清零
    return dat; //返回给函数的调用者printf
}

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
	
	while(sda){  //等待从机的ack
		Delay10ms();
	}
	
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

//地址addr，0为写，1为读
#define GXHT3L_ADDR_WRITE (0x44 << 1) + 0
#define GXHT3L_ADDR_READ (0x44 << 1) + 1

void gxht3l_init(){
	i2c_start();
	i2c_write_byte(GXHT3L_ADDR_WRITE);
  i2c_wait_ack();
	i2c_write_byte(0x21);//每秒一次
	i2c_wait_ack();
	i2c_write_byte(0x30);//高重复率
	i2c_wait_ack();
	i2c_stop();
}

void gxht3l_set_mode(){
	i2c_start();
	i2c_write_byte(GXHT3L_ADDR_WRITE);
  i2c_wait_ack();
	i2c_write_byte(0xE0);
	i2c_wait_ack();
	i2c_write_byte(0x00);
	i2c_wait_ack();
	i2c_stop();
}

void gxht3l_read(){
	unsigned char buffer[6];
	int i;
	unsigned short tem, hum;
  float temperature, humidity;
	i2c_start();
	i2c_write_byte(GXHT3L_ADDR_WRITE);
  i2c_wait_ack();
	for (i=0;i<6;i++){
		buffer[i] = i2c_read_byte();
	  if(i==5) i2c_nack();  //主机不响应，准备停止
		else i2c_ack();  //主机确认
	}
	i2c_stop();
	
	//合并两个8bit的数据为一个16bit的数据
    tem = (buffer[0] << 8) | buffer[1];
    hum = (buffer[3] << 8) | buffer[4];
    //进行温湿度转换
    temperature = (175.0 * (float) tem / 65535.0 - 45.0); // T = -45 + 175 * tem / (2^16-1)
    humidity = (100.0 * (float) hum / 65535.0); // RH = hum*100 / (2^16-1) 

	  //通过串口打印
    printf("temperature = %f humidity = %f\n",temperature,humidity);
}

void delay1s(){
	int t = 100;
	while(t--) Delay10ms();
}

void main(){
	uart_init();
	gxht3l_init();
	while(1){
		delay1s();
	  gxht3l_set_mode();
	  gxht3l_read();
	}
	
}