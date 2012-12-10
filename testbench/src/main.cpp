/*---------------------------------------------+
|                                              |
| Name: testbench/main.cpp                     |
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
#include "hal/onoff.h"
#include "hal/pgpipin.h"
#include "include/fakegpio.h"
#include "sys/pled.h"
#include "utils/pcircbuffer.h"
#include <avr/interrupt.h>
#include <util/delay.h>



char buff[100];



PCircBuffer<uint8_t,20> buforek;
uint16_t w=0;


uint8_t left()
{
	return buforek.space();
}


void addToBuff(uint16_t val)
{

	buforek.append(val);

	//uint8_t left;
	//left = buforek.capacity();
	//left -= buforek.size();

	sprintf(buff," => Adding=%d, space=%d\n",val,left());
	sim_puts(buff);

	int8_t err = buforek.errors();


	if(err==buforek.ERROR_OVERFL)
	{
		sprintf(buff,"Overflow %d\n",val);
		sim_puts(buff);
	}
}

int main(void)
{

	sprintf(buff,"\n\n");
    sim_puts(buff);

    TCCR1A = 0;
	TCCR1B = (1<<CS12)|(0<<CS11)|(1<<CS10)|(1<<WGM12);
	OCR1A=2001;
	TIMSK=(1<<OCIE1A);

	sei();



	for(uint8_t i=0; i<=25;i++)
	{
		addToBuff(w);
		w++;
	}


	while(1)
	{
		//_delay_ms(100);

		uint8_t vall;
		if(!buforek.isEmpty())
		{
			buforek.takeR(vall);
			sprintf(buff,"<= Value=%d\n",vall);
			sim_puts(buff);
		}
	}

    return 0;
}

#define ILE 1

ISR(TIMER1_COMPA_vect)
{
	addToBuff(w);
	w++;
}
