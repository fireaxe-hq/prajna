#include "prajna.h"
#include "common.h"
#include <execinfo.h>
#include "psApplet.h"

int PsApplet::trigger(char argc, char **argv)
{
	proc_sts_t *p = NULL;
	char tty[20];
	char *endp;
	char stime_str[6];
	unsigned int sut;
	unsigned int elapsed;
	unsigned int cstime, cutime;

	printf("pid    ppid   pgid   sid    uid    gid   sts   tty         "
			"STIME    TIME     CSTIME     CTIME      "
			"exe                         argv0            comm\n");

	while ((p = proc_scan(p)) != NULL) {
		if (p->tty_major == 136)
			strcpy(tty, "pts");
		else if (p->tty_major == 4) {
			strcpy(tty, "tty");
			if (p->tty_minor >= 64) {
				p->tty_minor -= 64;
				strcat(tty, "S");
			}
		} else
			sprintf(tty, "%d:", p->tty_major);

		sprintf(tty, "%s%d\t", tty, p->tty_minor);
		sut = (p->stime + p->utime) / 100;
		elapsed = (p->start_time) / 100;
		cstime = (p->cstime) / 100;
		cutime = (p->cutime) / 100;
		printf("%-6u %-6u %-6u %-6u %-6u %-6u %c    %6s "
				"%02u:%02u:%02u  %02u:%02u:%02u "
				"%02u:%02u:%02u  %02u:%02u:%02u "
				"%-028s %-016s %s\n", 
				p->pid, p->ppid, p->pgid, p->sid, p->uid, p->gid, p->state[0], tty,  
				elapsed / 3600, (elapsed %3600) / 60, elapsed % 60, 
				sut / 3600, (sut % 3600) / 60, sut % 60, 
				cstime / 3600, (cstime %3600) / 60, cstime % 60, 
				cutime / 3600, (cutime %3600) / 60, cutime % 60, 
				p->exe, p->comm, p->argv0);
	}

	return 0;
}

void PsApplet::help(void)
{
	printf("help info:\n");
	printf("Usage: %s\n", this->get_name().c_str());
}

applet_install(PsApplet);
applet_unstall(PsApplet);

