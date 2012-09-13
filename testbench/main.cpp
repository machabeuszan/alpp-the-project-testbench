/*
 */

#include <avr/io.h>

//#include "hal/gpio.h"

#define DEBUG true

#ifdef DEBUG
    #include <stdio.h>
    #define SPECIAL_OUT_PORT (*((volatile char *)0x20))
    #define SPECIAL_IN_PORT (*((volatile char *)0x22))
#endif

#ifdef DEBUG
    void debug_puts(const char * str)
    {
        const char *c;
        for(c=str;*c;c++)
        {
            SPECIAL_OUT_PORT=*c;
        }
    }
#endif

int main(void)
{
    #ifdef DEBUG
    char buff[100];
    #endif
    //uint8_t v=0;
    //A a(v);
    uint8_t a=56;
    //uint32_t *ptrA=(uint32_t)&a;
    uint16_t c=(uint16_t)&a;
    #ifdef DEBUG
    sprintf(buff,"Zmienna a=%d, &a=%d",a,c);
    debug_puts(buff);
//    debug_puts(buff);
    #endif
#if 0
    GPIO portD(PORTD,0xff,0x00);
    portD.setValue(0xf0);
    //PORTD=0xf0;
#endif
#if 0
    volatile uint8_t &ddr(*(&PORTD-1));
    ddr=0xff;
    //*(&PORTD-1)=0xff;
    PORTD=0xff;
    PORTD=0xf0;
#endif
#if 0
    initGP(PORTD,0xff,0x00);
    setGP(0xf0);
    //setGP()
#endif
    //*((volatile uint8_t *)(0x11))= 0xff;
    //*((volatile uint8_t *)(0x12)) = 0xff;
    //*((volatile uint8_t *)(0x12)) = 0xf0;
    //ddrd=0xff;
    //portd=0xff;
    //portd=0xf0;

    //while(1)
    //;

    return 0;
}
