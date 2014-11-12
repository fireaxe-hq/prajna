#include "common.h"
#include "exc_info.h"

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

void exc_install(char cmd)
{
	struct sigaction act;

	act.sa_sigaction = exc_myHandle;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGSEGV, &act, NULL);
}

