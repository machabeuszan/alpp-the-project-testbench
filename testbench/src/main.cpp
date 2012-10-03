/*---------------------------------------------+
|                                              |
| Name: Makefile                               |
|  Project: alpp                               |
|  Author: Adrian Ciesielski                   |
|  Creation Date: 2012-08-31                   |
|  Copyright: (c) 2012 by Adrian Ciesielski    |
|  License: See top of Makefile                |
|  Version: See top of Makefile                |
|                                              |
+---------------------------------------------*/


#include <avr/io.h>
#include "utils/simulSerial.h"
#include "hal/preg8.h"
//#include "hal/preg16.h"
//#include "hal/gpio.h"
#include "hal/onoff.h"
#include "hal/pgpopin.h"










int main(void)
{
    #ifdef SIM
    char buff[100];
    #endif

    volatile uint8_t fakerejestr=0b01010101;
    //volatile uint16_t fake2=0b0101010101010101;

    //PReg8 MyReg(fakerejestr);
    //My8Preg MyRejestr(fakerejestr);
    //PReg8<uint16_t> MyRej2(fake2);

    fakerejestr=0b01010101; //85

    //PReg8::set(fakerejestr,0b00110011,0b00001111);
    //PReg16::set(fake2,0b0011001100110011,0b0000111100001111);


	PORTD=0b01010101;
    PGpoPin led1(PORTD,3,1);

    led1.on();
    //led1.highZ(true);

    uint8_t a=0;



    a=PORTD;
    //uint8_t v=0;
    //A a(v);
    //a=PReg8::get(fakerejestr,a,0x0f);
    //MyReg.set(0xff,0x0f);
    //a=((bool)(fakerejestr&(1<<5)))^false;
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
