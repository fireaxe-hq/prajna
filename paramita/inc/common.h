#ifndef COMMON_H
#define COMMON_H

#include <signal.h>
#include <dirent.h>
#include <iostream>
#include <fstream>
#include <termios.h>
#include <poll.h>

#ifdef __cplusplus
extern "C"
{
#endif


#define NAME_MAX_LEN 20

/*! Transfer command from userspace to kernel. */
struct USR_CMD {
	char name[NAME_MAX_LEN]; /*!< the command */
	unsigned long para[8]; /*!< parameters, maximum 8 parameters are available. */
};

#ifdef __cplusplus
}
#endif

/*! add applet object into paramita object */
bool add_applet(void *applet);

/*! install applet into paramita */
#define applet_install(x) \
	x __tmp_##x; \
	void __applet_con_##x() __attribute__((constructor)); \
	void __applet_con_##x() \
	{ \
		add_applet(&__tmp_##x); \
	}

	/*! unstall applet from paramita */
#define applet_unstall(x) \
	void __applet_des_##x() __attribute__((destructor)); \
	void __applet_des_##x() \
	{ \
	}

/*! process status */
typedef struct proc_sts_t {
	DIR *dir;
	char *argv0;
	char *exe;
	unsigned long vsz, rss;
	unsigned long stime, utime;
	unsigned long cstime, cutime;
	unsigned long start_time;
	unsigned int pid;
	unsigned int ppid;
	unsigned int pgid;
	unsigned int sid;
	unsigned int uid;
	unsigned int gid;
	unsigned int tty_major, tty_minor;
	char state[4];
	char comm[16];
} proc_sts_t;

typedef struct jiffy_counts_t {
   unsigned long long user;
   unsigned long long nice;
   unsigned long long system;
   unsigned long long idle;
   unsigned long long iowait;
   unsigned long long irq;
   unsigned long long softirq;
   unsigned long long steal;
   unsigned long long guest;
   unsigned long long guest_nice;
} jiffy_counts_t;

extern proc_sts_t *proc_scan(proc_sts_t *sp);
extern int read_cpu_jiffy(int cpu_num, jiffy_counts_t *p_jif);
#endif /* COMMON_H */

