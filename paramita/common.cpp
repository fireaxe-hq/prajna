#include "prajna.h"
#include "common.h"
#include <execinfo.h>

static int read_to_buf(const char *filename, void *buf)
{
	int fd;
	int ret = -1;

	fd = open(filename, O_RDONLY);
	if (fd >= 0) {
		ret = read(fd, buf, 1023);
		close(fd);
	}
	((char*)buf)[ret > 0 ? ret : 0] = '\0';
	return ret;
}

static char *alloc_readlink(const char *path)
{
	char *link = NULL;
	int bufsize = 0, readsize = 0;

	do {
		bufsize += 40;
		link = (char*)realloc(link, bufsize);
		readsize = readlink(path, link, bufsize);
		if (readsize == -1) {
			free(link);
			return NULL;
		}
	} while (bufsize < readsize + 1);
	link[readsize] = 0;

	return link;
}

proc_sts_t *proc_scan(proc_sts_t *sp)
{
	struct dirent *entry;
	char filename[sizeof("/proc/%u/task/%u/cmdline") + sizeof(int) * 3 * 2];
	char *filename_tail;
	unsigned int pid;
	char buf[1024];
	char *cp, *comm1;
	int tty, n;
	long tasknice;

	if (!sp) {
		sp = (proc_sts_t*)malloc(sizeof(proc_sts_t));
		memset((char*)sp, 0, sizeof(proc_sts_t));
		sp->dir = opendir("/proc");
		if (!sp->dir) {
			printf("opendir \"/proc\" failed!\n");
			return NULL;
		}

	}

	while (1) {

		entry = readdir(sp->dir);
		if (!entry) {
			closedir(sp->dir);
			if (!sp->argv0)
				free(sp->argv0);
			free(sp);
			return NULL;
		}

		pid = strtoul(entry->d_name, NULL, 10);
		sp->pid = pid;

		sprintf(filename, "/proc/%u/", pid);
		filename_tail  = filename + strlen(filename);

		strcpy(filename_tail, "stat");
		n = read_to_buf(filename, buf);
		if (n < 0)
			continue;
		cp = strrchr(buf, ')');
		cp[0] = 0;
		comm1 = strchr(buf, '(');
		strncpy(sp->comm, comm1 + 1, sizeof(sp->comm));
		/* see proc(5) for details on this */
		sscanf(cp + 2, 
				"%c %u "               /* state, ppid */
				"%u %u %d %*s "        /* pgid, sid, tty, tpgid */
				"%*s %*s %*s %*s %*s " /* flags, min_flt, cmin_flt, maj_flt, cmaj_flt */
				"%lu %lu "             /* utime, stime */
				"%*s %*s %*s "         /* cutime, cstime, priority */
				"%ld "                 /* nice */
				"%*s %*s "             /* timeout, it_real_value */
				"%lu "                 /* start_time */
				"%lu "                 /* vsize */
				"%lu ",                 /* rss */
				sp->state, &sp->ppid,
				&sp->pgid, &sp->sid, &tty,
				&sp->utime, &sp->stime,
				&tasknice,
				&sp->start_time,
				&sp->vsz,
				&sp->rss);
		sp->tty_major = (tty >> 8) & 0xfff;
		sp->tty_minor = (tty & 0xff) | ((tty >> 12) & 0xfff00);
		sp->vsz = sp->vsz >> 10;
		if (sp->vsz == 0 && sp->state[0] != 'Z')
			sp->state[1] = 'W';
		else
			sp->state[1] = ' ';
		if (tasknice < 0)
			sp->state[2] = '<';
		else if (tasknice)
			sp->state[2] = 'N';
		else
			sp->state[2] = ' ';

		strcpy(filename_tail, "exe");
		sp->exe = alloc_readlink(filename);

		strcpy(filename_tail, "cmdline");
		n = read_to_buf(filename, buf);
		if (n <= 0)
			break;
		sp->argv0 = (char*)malloc(n + 1);
		strcpy(sp->argv0, buf);
		break;
	}

	return sp;
}

