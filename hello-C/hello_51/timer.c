#include <reg52.h>

#define TIMS (65536-9216)  //设置预装载值
sbit led = P2^7;  //一颗LED灯的管脚
unsigned int count = 0;  //全局计数
                  

// 用定时器每隔10ms翻转led灯的状态
void main()
{
	      //设置模式
        TMOD = 0x01;                    //配置定时器0为16位定时器，TH0、TL0全用
        
	      //预装载值
	      TH0 = TIMS >> 8;                //设置定时初值高8位
        TL0 = TIMS;                     //设置定时初值低8位
        
	      //中断使能
	      ET0 = 1;  //开启定时器0中断                                          
        EA  = 1;  //开启全局中断                                                      
        
	      //开关放在最后
	      TR0 = 1;  //定时器0开始计数        
        while(1);
}

//10ms执行一次
void Timer0() interrupt 1  //timer 0 的中断号是 1
{
        //每次产生中断后重新设置下次定时器初值 - 10毫秒产生1次中断
        TH0 = TIMS >> 8;
        TL0 = TIMS;
        //1000毫秒执行一次P1电平反转
        count++;
        if(count >= 100)
        {
                led = ~led;
                count = 0;
        }
}