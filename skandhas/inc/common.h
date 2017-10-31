#ifndef COMMON_H
#define COMMON_H

#include <linux/types.h>
#include <signal.h>

#ifdef __cplusplus
extern "C"
{
#endif

/*! dump memory content */
void dump_mem
	(
	unsigned char *base, /*!< base address */
	unsigned long size /*!< size of memory in char */
	);
/*! dump stack frame content */
void dump_stackframe
	(
	unsigned long fp /*!< value of fp register */
	);
/*! dump register values */
void dump_register
	(
	struct sigcontext *pt_reg /*!< pointer to register list */
	);
/*! dump function call list */
void dump_trace
	(
	void *array[], /*!< address of trace list */
	int size /*!< size of trace list */
	);

#ifdef __cplusplus
}
#endif

/*! add bug object into skandhas object */
bool add_bug(void *bug);

/*! install bug into skandhas */
#define bug_install(x) \
	x __tmp_##x; \
	void __bug_con_##x() __attribute__((constructor)); \
	void __bug_con_##x() \
	{ \
		add_bug(&__tmp_##x); \
	}

	/*! unstall bug from skandhas */
#define bug_unstall(x) \
	void __bug_des_##x() __attribute__((destructor)); \
	void __bug_des_##x() \
	{ \
	}

#endif /* COMMON_H */

