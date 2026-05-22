#include <reg52.h>

typedef unsigned char uchar;
typedef unsigned int  uint;

sbit Beep = P2^1;
bit flag = 0;

uchar toneH, toneL;   // 定时器高低位初值
uchar musicIndex = 0; // 乐谱下标

// 新年快乐乐谱：高8位,低8位,发音时长
uchar code music[] = {
    0xfc,0x44,0x7f, 0xfc,0x44,0x7f, 0xfc,0x44,0xff, 0xfa,0x68,0xff,
    0xfd,0x23,0x7f, 0xfd,0x23,0x7f, 0xfd,0x23,0xff, 0xfc,0x44,0xff,
    0xfc,0x44,0x7f, 0xfd,0x23,0x7f, 0xfd,0x82,0xff, 0xfd,0x82,0xff,
    0xfd,0x23,0x7f, 0xfd,0x23,0x7f, 0xfc,0xac,0xff, 0xff,0xff,0xff,
    0xfc,0xac,0x7f, 0xfd,0x23,0x7f, 0xfd,0x34,0xff, 0xfd,0x34,0xff,
    0xfd,0x23,0x7f, 0xfc,0xac,0x7f, 0xfd,0x23,0xff, 0xfc,0x44,0xff,
    0xfc,0x44,0x7f, 0xfd,0x23,0x7f, 0xfc,0xac,0xff, 0xfa,0x68,0xff,
    0xfc,0x0c,0x7f, 0xfc,0xac,0x7f, 0xfc,0x44,0xff, 0xff,0xff,0xff,
    0x00
};

// 12MHz精准毫秒延时
void delay_ms(uint xms)
{
    uint i,j;
    for(i=xms;i>0;i--)
        for(j=124;j>0;j--);
}

// 定时器0中断：翻转蜂鸣器电平
void Timer0_ISR() interrupt 1
{
    TH0 = toneH;
    TL0 = toneL;
    Beep = !Beep;  // 最简电平翻转，替代if判断
}

// 系统初始化
void System_Init(void)
{
    TMOD |= 0x01;  // T0 16位定时模式
    ET0 = 1;
    EA  = 1;
    TR0 = 0;       // 初始关闭定时器
    Beep = 1;      // 蜂鸣器初始静默
}

void main(void)
{
    uchar playTime;
    System_Init();
    
    while(1)
    {
        // 正常发音音符
        if(music[musicIndex] != 0xFF && music[musicIndex] != 0x00)
        {
            TR0 = 0;                // 停止发声，切换音调无杂音
            toneH = music[musicIndex];
            toneL = music[musicIndex+1];
            playTime = music[musicIndex+2];
            
            TH0 = toneH;
            TL0 = toneL;
            TR0 = 1;                // 开启定时器发声
            delay_ms(playTime);
            musicIndex += 3;
        }
        // 休止符，静音停顿
        else if(music[musicIndex] == 0xFF)
        {
            TR0 = 0;
            playTime = music[musicIndex+2];
            delay_ms(playTime);
            musicIndex += 3;
        }
        // 乐曲结束，延时复位重头播放
        else if(music[musicIndex] == 0x00)
        {
            TR0 = 0;
            delay_ms(2000);
            musicIndex = 0;
            Beep = 1;
        }
    }
}