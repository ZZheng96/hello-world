#include <reg52.h>

sbit led = P2^7;

//??????
void delay_ms(unsigned int xms)   //@12MHz
{
    unsigned int i, j;
    for(i=xms;i>0;i--)
    {
        for(j=124;j>0;j--)
        {}
    }
}

void main()
{
    while(1)
    {
        led = 0;
        delay_ms(500);
        led = 1;
        delay_ms(500);
    }
}