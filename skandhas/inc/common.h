#ifndef COMMON_H
#define COMMON_H

#include <signal.h>

#ifdef __cplusplus
extern "C"
{
#endif

void dump_mem(unsigned char *base, unsigned long size);
void dump_stackframe(unsigned long fp);
void dump_register(struct sigcontext *pt_reg);
void dump_trace(void *array[], int size);

#ifdef __cplusplus
}
#endif

bool add_bug(void *bug);

#define bug_install(x) \
	x __tmp_##x; \
	void __bug_con_##x() __attribute__((constructor)); \
	void __bug_con_##x() \
	{ \
		add_bug(&__tmp_##x); \
	}

#define bug_unstall(x) \
	void __bug_des_##x() __attribute__((destructor)); \
	void __bug_des_##x() \
	{ \
	}

#endif /* COMMON_H */

