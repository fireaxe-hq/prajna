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
	printf("  %s       tmp info\n", this->get_name().c_str());
}

applet_install(TmpApplet);
applet_unstall(TmpApplet);

