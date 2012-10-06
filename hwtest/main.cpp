/*
 */

#include <avr/io.h>
#include <util/delay.h>
#include "sys/pled.h"
#include "hal/pgpipin.h"

int main(void)
{

    // Insert code
    PLed dioda(PORTB,4,0);
    PGpiPin sw(PORTB,3,0);


    while(1)
    {
		_delay_ms(100);
		if(sw.isOn())
		{
			dioda.off();
		} else {
			dioda.on();
		}
    }


    return 0;
}
