#include "prajna.h"
#include "common.h"
#include <execinfo.h>
#include "appletTemplate.h"

int appletTemplate::trigger(char argc, char **argv)
{
	return 0
}

void appletTemplate::help(void)
{
	printf("  tmp       tmp info\n");
}

applet_install(appletTemplate)
applet_unstall(appletTemplate)

