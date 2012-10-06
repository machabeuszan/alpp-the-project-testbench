#ifndef FAKEGPIO_H_INCLUDED
#define FAKEGPIO_H_INCLUDED


#define FPORT(x) FPORT ## x
#define FDDR(x) FDDR ## x
#define FPIN(x) FPIN ## x

#define REGTYPE volatile uint8_t
#define FAKESET(x) REGTYPE FPORT(x); \
				   REGTYPE FDDR(x) = (*(&FPORT(x)-1)); \
				   REGTYPE FPIN(x) = (*(&FPORT(x)-2));

FAKESET(A);
FAKESET(B);
FAKESET(C);
FAKESET(D);
FAKESET(E);
FAKESET(F);

#endif // FAKEGPIO_H_INCLUDED
