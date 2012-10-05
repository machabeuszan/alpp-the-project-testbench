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
#include "hal/pgpipin.h"





int main(void)
{
    #ifdef SIM
    char buff[100];
    #endif

    //volatile uint8_t fakerejestr=0b01010101;
	//PIND=0xf0;



	volatile uint8_t FPORTB;

	volatile uint8_t &FDDRB=(*(&FPORTB-1));
	volatile uint8_t &FPINB=(*(&FPORTB-2));

	PGpiPin sw(FPORTB,6,0);
	//FPORTB=0xff;
	sw.deactivate();


	FPINB=(1<<6);

	uint16_t a=sw.isOn();


    uint16_t c=(uint16_t)&a;
    #ifdef SIM
    sprintf(buff,"\nZmienna a=%u, &a=%d\n\n",a,c);
    sim_puts(buff);
    #endif



    //while(1)
    //;

    return 0;
}
