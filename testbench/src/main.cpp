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
//#include "hal/preg16.h"
//#include "hal/gpio.h"
#include "hal/onoff.h"
#include "hal/pgpipin.h"
#include "include/fakegpio.h"
#include "sys/pled.h"
//#include "utils/pcircbuffer.h"
#include <avr/interrupt.h>
#include <util/delay.h>



char buff[100];




template <class T, uint8_t Capacity>
class PCircBuffer
{
	public:
		enum ERRS {
			ERROR_NO	= 0,
			ERROR_OVERFL	= _BV(1),
			ERROR_NOMORE	= _BV(2),
			ERROR_NOSPACE	= _BV(3)
		};
		PCircBuffer();
		void clear();
		void enqueue(T val);
		//int8_t enqueue(T &rVal);
		T dequeue();
		//int8_t dequeue(T &rVal);
		bool isFull();
		bool isEmpty();
		uint8_t size();
		uint8_t capacity();
		int8_t errors();
		void fill(uint8_t numOfElement, T &value);
	protected:
	private:
		T container[Capacity];
		uint8_t tail;
		uint8_t head;
		volatile uint8_t len;
		const uint8_t cap;
		T emptyRet;
		int8_t error_occured;

		void next(uint8_t &val);

};

template <class T, uint8_t Capacity>
PCircBuffer<T,Capacity>::PCircBuffer() :
	tail(1)
	,head(0)
	,len(0)
	,cap(Capacity)
{
}

template <class T, uint8_t C>
uint8_t PCircBuffer<T,C>::size()
{
	return len;
}

template <class T, uint8_t C>
uint8_t PCircBuffer<T,C>::capacity()
{
	return cap;
}

template <class T, uint8_t C>
bool PCircBuffer<T,C>::isEmpty()
{
	return (len==0);
}

template <class T, uint8_t C>
bool PCircBuffer<T,C>::isFull()
{
	return (len==cap);
}

template <class T, uint8_t C>
void PCircBuffer<T,C>::next(uint8_t &val)
{
	val = (val + 1) % cap;
}


template <class T, uint8_t C>
void PCircBuffer<T,C>::enqueue(T val)
{
	next(head);
	if(isFull())
	{
		error_occured |= ERROR_OVERFL;
		next(tail);
	} else {
		len++;
	}
	container[head]=val;
}

void someDelay(uint8_t loops = 5)
{
	for(uint8_t i=0;i<=loops;i++)
	{
		_delay_ms(10);
		sprintf(buff,"r");
		sim_puts(buff);
	}
}

template <class T, uint8_t C>
T PCircBuffer<T,C>::dequeue()
{
	T ret;
	if(!isEmpty())
	{
		ret = container[tail];
		someDelay(10);
		next(tail);
		len--;
	} else {
		ret = emptyRet;
		error_occured |= ERROR_NOMORE;
	}

	return ret;
}

template <class T, uint8_t C>
int8_t PCircBuffer<T,C>::errors()
{
	int8_t err = error_occured;
	error_occured = ERROR_NO;
	return err;
}


PCircBuffer<uint8_t,20> buforek;
uint16_t w=0;


uint8_t left()
{
	return buforek.capacity() - buforek.size();
}


void addToBuff(uint16_t val)
{

	buforek.enqueue(val);

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
    #ifdef SIM
    #endif


	sprintf(buff,"\n\n");
    sim_puts(buff);

    TCCR1A = 0;
	TCCR1B = (1<<CS12)|(0<<CS11)|(1<<CS10)|(1<<WGM12);
	OCR1A=4001;
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

		if(!buforek.isEmpty())
		{
			sprintf(buff,"<= Value=%d\n",buforek.dequeue());
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
