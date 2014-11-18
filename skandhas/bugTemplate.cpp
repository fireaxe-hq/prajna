#include "prajna.h"
#include "common.h"
#include <execinfo.h>
#include "bugTemplate.h"

void bugTemplate::trigger(void)
{
}

bool bugTemplate::dbg_en(bool val)
{
	struct sigaction act;

	if (val) {
	}
}

void bugTemplate::help(void)
{
	printf("  tmp       tmp info\n");
}

bug_install(bugTemplate)
bug_unstall(bugTemplate)

