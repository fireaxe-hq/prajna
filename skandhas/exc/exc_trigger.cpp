#include "prajna.h"
#include "exc_trigger.h"

static int ab02=1;
static void (*p)(int);

static void ab2(int c2)
{
	memset((void*)0x0b, 0, 10);
}

static void abc(int c)
{
	p = ab2;
	p(c+2);
}

void trig_exc_mem(void)
{
	abc(ab02);
}

void trig_exc_text(void)
{
	void (*q)(int);

	q = NULL;
	q(1);
}

