#include "prajna.h"
#include "common.h"
#include <execinfo.h>
#include "excProgramBug.h"

static int ab02=1;
static void (*p)(int);

void ExcProgramBug::trigger(void)
{
	void (*q)(int);
	q = NULL;
	q(1);
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

bool ExcProgramBug::dbg_en(bool val)
{
	struct sigaction act;

	if (val) {
		act.sa_sigaction = exc_myHandle;
		act.sa_flags = SA_SIGINFO;
		sigaction(SIGSEGV, &act, NULL);
	}
}

void ExcProgramBug::help(void)
{
	printf("  program       program invalid exception\n");
}

bug_install(ExcProgramBug)
bug_unstall(ExcProgramBug)

