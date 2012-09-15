/*
 */

#include <avr/io.h>
#include "utils/simulSerial.h"

//#include "hal/gpio.h"

enum PREG_LEN {
    PREG_8  = 1,
    PREG_16 = 2,
    PREG_32 = 4
};

enum PONOFF {
    ON=~0,
    OFF=0x00
};

template <class T>
class PReg8
{
    public:
        PReg8(volatile T& reg);
        void set(const T& value, const T& mask);
        static void set(volatile T& reg, const T& value, const T& mask);
        T get(const T& mask);
        static T get(volatile T& reg, const T& mask);
    private:
        volatile T& regHandle;
	//void valWithMask(volatile T &reg, T& val, T& mask);
};

template <class T> PReg8<T>::PReg8(volatile T& reg): regHandle(reg)
{
  ;
}

/*template <class T> void PReg8<T>::valWithMask(volatile T &reg, T& val, T& mask)
{

}*/

template <class T> void PReg8<T>::set(const T& value, const T& mask)
{
  set(regHandle,value,mask);
}

template <class T> void PReg8<T>::set(volatile T& reg, const T& value, const T& mask)
{
  T a=value&mask;
  T b=value|(~mask);
  reg=(b&reg);
  reg=a|reg;
}

template <class T> T PReg8<T>::get(const T& mask)
{
  get(regHandle,mask);
}

template <class T> T PReg8<T>::get(volatile T& reg, const T& mask)
{
  T val=reg;
  T a=val&mask;
  T b=val|mask;
  val=a|(b&reg);
  return val;
}

class My8Preg:public PReg8<uint8_t>
{
    public:
        My8Preg(volatile uint8_t& reg);
};

My8Preg::My8Preg(volatile uint8_t& reg): PReg8(reg)
{
    ;
}

int main(void)
{
    #ifdef SIM
    char buff[100];
    #endif

    volatile uint8_t fakerejestr;
    volatile uint16_t fake2=0b0101010101010101;

    My8Preg MyRejestr(fakerejestr);
    //PReg8<uint16_t> MyRej2(fake2);

    fakerejestr=0b01010101; //85
    //            value = 51, mask = 15
    MyRejestr.set(0b00110011,0b00001111);


    PReg8<uint16_t>::set(fake2,0b0011001100110011,0b0000111100001111);




    //uint8_t v=0;
    //A a(v);
    uint8_t a=fakerejestr;
    //uint16_t a=fake2;


    //uint32_t *ptrA=(uint32_t)&a;
    uint16_t c=(uint16_t)&a;
    #ifdef SIM
    sprintf(buff,"Zmienna a=%u, &a=%d",a,c);
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
