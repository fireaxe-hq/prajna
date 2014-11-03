#include <stdlib.h>
#include <stdio.h>

extern ab02;
void (*p)(int);

extern void ab2(int c2);

void abc(int c)
{
	p = ab2;
	p(c+2);
}

