//看门狗
#include <reg52.h>

sfr WDT_CONTR=0xe1; //无需这句是否正常？
sbit led=P2^7;

void delayms(unsigned int xms) {
    unsigned int i,j;
    for (i=xms;i>0;i--)
    for(j=110;j>0;j--);
}

void main()
{
    WDT_CONTR=0x35;  //启动看门狗，开始重新计数，预分频数为64，2s不喂狗会溢出并复位
    led=0;
    delayms(500);
    led=1;
    while(1)
    {
        delayms(3000);
        WDT_CONTR=0x35;
    }
}
