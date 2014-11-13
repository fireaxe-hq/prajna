#include "prajna.h"
#include "common.h"
#include <execinfo.h>
#include "excDataBug.h"

static int ab02=1;
static void (*p)(int);

static void ab2(int c2)
{
	memset((void*)0x0b, 0, 10);
}

static void abc(int c)
{
	p = ab2;
	p(c+2);
}

void ExcDataBug::trigger(void)
{
	abc(ab02);
}

static void exc_myHandle(int signo, siginfo_t *info, void *ptr)
{
	struct sigcontext *pt_reg = &((ucontext_t*)ptr)->uc_mcontext;
	void *array[10];
	size_t size;

	printf("\nException signal: %d\n", signo);
	
	/* show register info */
	dump_register(pt_reg);

	/* show stack info*/
	printf("\nStart dumpping stack:\n");
	dump_stackframe(pt_reg->arm_fp);

	/* show function tracking list */
	array[0] = (void*)pt_reg->arm_pc;
	array[1] = (void*)pt_reg->arm_lr;
	size = backtrace(array+2, 8);
	size += 2;
	dump_trace(array, size);

	exit(signo);
}

bool ExcDataBug::dbg_en(bool val)
{
	struct sigaction act;

	if (val) {
		act.sa_sigaction = exc_myHandle;
		act.sa_flags = SA_SIGINFO;
		sigaction(SIGSEGV, &act, NULL);
	}
}

void ExcDataBug::help(void)
{
	printf("  data          address access exception\n");
}

bug_install(ExcDataBug)
bug_unstall(ExcDataBug)

