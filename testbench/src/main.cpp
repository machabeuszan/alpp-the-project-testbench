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








class MLT{
public:
  uint8_t control:6;
  uint8_t rtr:1;
  uint8_t ext:1;

};

int main(void)
{
    #ifdef SIM
    char buff[100];
    #endif

//    volatile uint8_t fakerejestr=0b01010101;

	uint16_t a=0;

	MLT dupa;
	dupa.control=0x3d;
	dupa.rtr=1;
	dupa.ext=1;

	a=(dupa.control<<2)|(dupa.rtr<<1)|(dupa.ext);




    //uint32_t *ptrA=(uint32_t)&a;
    uint16_t c=(uint16_t)&a;
    #ifdef SIM
    sprintf(buff,"\nZmienna a=%u, &a=%d\n\n",a,c);
    sim_puts(buff);
    #endif



    //while(1)
    //;

    return 0;
}
