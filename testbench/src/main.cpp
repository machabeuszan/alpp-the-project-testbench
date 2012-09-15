/*
 */

#include <avr/io.h>
#include "utils/simulSerial.h"
#include "hal/preg8.h"

//#include "hal/gpio.h"


int main(void)
{
    #ifdef SIM
    char buff[100];
    #endif

    volatile uint8_t fakerejestr;
    //volatile uint16_t fake2=0b0101010101010101;

    //My8Preg MyRejestr(fakerejestr);
    //PReg8<uint16_t> MyRej2(fake2);

    fakerejestr=0b01010101; //85

    PReg8::set(fakerejestr,0b00110011,0b00001111);




    //uint8_t v=0;
    //A a(v);
    uint8_t a=fakerejestr;
    //uint16_t a=fake2;


    //uint32_t *ptrA=(uint32_t)&a;
    uint16_t c=(uint16_t)&a;
    #ifdef SIM
    sprintf(buff,"\nZmienna a=%u, &a=%d\n\n",a,c);
    sim_puts(buff);
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
