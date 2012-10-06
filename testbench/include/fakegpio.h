/*---------------------------------------------+
|                                              |
| Name: fakegpio.h                             |
|  Project: alpp                               |
|  Author: Adrian Ciesielski                   |
|  Creation Date: 2012-10-06                   |
|  Copyright: (c) 2012 by Adrian Ciesielski    |
|  License: See top of Makefile                |
|  Version: See top of Makefile                |
|                                              |
+---------------------------------------------*/

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
