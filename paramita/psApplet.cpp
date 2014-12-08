#include "prajna.h"
#include "common.h"
#include <execinfo.h>
#include "psApplet.h"

int PsApplet::trigger(char argc, char **argv)
{
	printf("show ps info\n");
	return 0;
}

void PsApplet::help(void)
{
	printf("help info:\n");
	printf("Usage: ps\n");
}

applet_install(PsApplet)
applet_unstall(PsApplet)

