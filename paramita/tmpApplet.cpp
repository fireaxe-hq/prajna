#include "prajna.h"
#include "common.h"
#include <execinfo.h>
#include "tmpApplet.h"

int TmpApplet::trigger(char argc, char **argv)
{
	return 0
}

void TmpApplet::help(void)
{
	printf("  tmp       tmp info\n");
}

applet_install(TmpApplet)
applet_unstall(TmpApplet)

