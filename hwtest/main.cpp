/*---------------------------------------------+
|                                              |
| Name: hwtest/main.cpp                     |
|  Project: alpp                               |
|  Author: Adrian Ciesielski                   |
|  Creation Date: 2012-10-06                  |
|  Copyright: (c) 2012 by Adrian Ciesielski    |
|  License: See top of Makefile                |
|  Version: See top of Makefile                |
|                                              |
+---------------------------------------------*/

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
