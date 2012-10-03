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


class PGpoPin
{
public:
    PGpoPin(volatile uint8_t &port, const uint8_t pin, bool offState);
    void set(bool value);
    bool get();
    void on();
    void off();
    void toggle();
    void highZ(const bool enable);

private:
    volatile uint8_t &PORT;
    volatile uint8_t &DDR;
    uint8_t PINmask;
    bool os;


};

PGpoPin::PGpoPin(volatile uint8_t &port, const uint8_t pin, bool offState):PORT(port),DDR(*(&port-1)),PINmask(1<<pin),os(offState)
{
    highZ(false);
}

inline void PGpoPin::set(bool value)
{
    value^=os;
    PReg8::set(PORT,0xff*value,PINmask);
}

inline bool PGpoPin::get()
{
    return ((bool)(PORT&PINmask))^os;
}

inline void PGpoPin::on()
{
    set(true);
}

inline void PGpoPin::off()
{
    set(false);
}

inline void PGpoPin::toggle()
{
    PORT^=PINmask;
}

void PGpoPin::highZ(const bool enable)
{
    if(enable)
        DDR&=~(PINmask);
    else
        DDR|=(PINmask);
}




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


    PGpoPin led1(PORTD,4,0);

    led1.off();
    led1.highZ(true);

    uint8_t a=0;

    a=DDRD;
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
