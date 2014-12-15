#include "prajna.h"
#include "common.h"
#include <execinfo.h>
#include "topApplet.h"

static int top_cmp(const void *a, const void *b)
{
	top_info *t1, *t2;

	t1 = (top_info*)a;
	t2 = (top_info*)b;

	return (t1->proc_cpu_ratio < t2->proc_cpu_ratio) ? 1 : -1;
}

static int  handle_input(void)
{
	struct pollfd pfd;
	char buf;

	pfd.fd = 0;
	pfd.events = POLLIN;

	if (0 == poll(&pfd, 1, 1000))
		return -1;

	if ( 0 >= read(STDIN_FILENO, &buf, 1))
		return -1;

	if ('q' != buf)
		return -1;

	return 0;
}

int TopApplet::trigger(char argc, char **argv)
{
	proc_sts_t *p = NULL;
	jiffy_counts_t jif;
	char tty[20];
	char *endp;
	char stime_str[6];
	proc_sts_t *proc;
	unsigned int cpu_time1, cpu_time2;
	unsigned int idle_time1, idle_time2;
	unsigned int proc_time1, proc_time2;
	float ratio = 0;
	int proc_count = 0;
	int top_count = 0;
	int i;
	top_info top[SHOW_NUM + 1];
	int delay = 5;
	int first = 1;

	proc = (proc_sts_t*)malloc(MAX_PROC_NUM * sizeof(proc_sts_t));
	if (NULL == proc) {
		printf("err: malloc proc array failed.\n");
		return -1;
	}

	while (1) {
		proc_count = 0;
		top_count = 0;

		if (-1 == read_cpu_jiffy(-1, &jif)) {
			printf("err: read_cpu_jiffy failed\n");
			goto quit;
		}
		cpu_time1 = (jif.user + jif.nice + jif.system + jif.idle + 
				jif.iowait + jif.irq + jif.softirq + jif.steal + 
				jif.guest + jif.guest_nice);
		idle_time1 = jif.idle;

		for (proc_count = 0; 
				((p = proc_scan(p)) != NULL) && (proc_count < MAX_PROC_NUM); 
				proc_count++) {
			memcpy(proc + proc_count, p, sizeof(proc_sts_t));
			proc_count++;
		}

		for (i = 0; i< delay; i++) {
			usleep(1000);
			if (0 == handle_input())
				goto quit;
			if (first == 1) {
				first = 0;
				break;
			}
		}

		if (-1 == read_cpu_jiffy(-1, &jif)) {
			printf("err: read_cpu_jiffy failed\n");
			goto quit;
		}
		cpu_time2 = (jif.user + jif.nice + jif.system + jif.idle + 
				jif.iowait + jif.irq + jif.softirq + jif.steal + 
				jif.guest + jif.guest_nice);
		idle_time2 = jif.idle;

		while ((p = proc_scan(p)) != NULL) {
			for (i = 0; i < proc_count; i++)
				if (p->pid == (proc + i)->pid)
					break;

			if (i >= proc_count)
				continue;

			proc_time2 = (p->stime + p->utime + p->cstime + p->cutime);
			proc_time1 = ((proc + i)->stime + (proc + i)->utime + 
					(proc + i)->cstime + (proc + i)->cutime);
			top[top_count].proc_cpu_ratio = (proc_time2 - proc_time1); 
			top[top_count].p = (proc + i);

			qsort(top, top_count + 1, sizeof(top_info), top_cmp);

			if (top_count < SHOW_NUM) {
				top_count++;
			}
		}

		printf("cpu rate is %3.02f%%\n", 
				100 - (idle_time2 - idle_time1) * 100.0 / (cpu_time2 - cpu_time1));
		printf("pid    ppid    %%cpu  command\n");
		for (i = 0; i < top_count; i++) {
			printf("%-6u %-6u %5.2f  %s\n", 
					top[i].p->pid, top[i].p->ppid, 
					top[i].proc_cpu_ratio * 100.0 / (cpu_time2 - cpu_time1), 
					top[i].p->comm);
		}

	}

quit:
	printf("\n");
	free(proc);

	return 0;
}

void TopApplet::help(void)
{
	printf("  %s       show resource info\n", this->get_name().c_str());
}

applet_install(TopApplet);
applet_unstall(TopApplet);

