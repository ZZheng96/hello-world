// #include <reg52.h>

// sbit led = P2^7;

// //??????
// void delay_ms(unsigned int xms)   //@12MHz
// {
//     unsigned int i, j;
//     for(i=xms;i>0;i--)
//     {
//         for(j=124;j>0;j--)
//         {}
//     }
// }

// void main()
// {
//     while(1)
//     {
//         led = 0;
//         delay_ms(500);
//         led = 1;
//         delay_ms(500);
//     }
// }

#include <reg52.h>

void delay_ms(unsigned int xms) 
{
    unsigned int i, j;
    for(i=xms;i>0;i--)
    {
        for(j=124;j>0;j--) // 1 ms
        {}
    }
}

void open_led(unsigned int num){
    P2 = 0xFF & ~(1 << num);  // P2 defined in <reg52.h>
}

void main()
{
    while(1)
    {
        open_led(7);  // 2.7, 2.6, 2.5
        delay_ms(500);
        open_led(6);
        delay_ms(500);
        open_led(5);
        delay_ms(500);
    }
}
