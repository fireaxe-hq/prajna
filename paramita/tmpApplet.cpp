#include "prajna.h"
#include "common.h"
#include <execinfo.h>
#include "tmpApplet.h"

int tmpApplet::trigger(char argc, char **argv)
{
	return 0
}

void tmpApplet::help(void)
{
	printf("  tmp       tmp info\n");
}

applet_install(tmpApplet)
applet_unstall(tmpApplet)

