#include <stdlib.h>
#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include "prajna.h"

static void memdump(unsigned char *base, unsigned long size)
{
	int i;

	for (i = 0; i < size; i++) {
		if ((i%4 == 0) && i)
			printf(" ");
		if (i%(4*4) == 0)
			printf("\n%08x: ", (unsigned long)(base + i));
		printf("%02x", *(base + i));
	}

	printf("\n");
}

static void dump_stackframe(unsigned fp)
{
	unsigned long size;

	if (0 == fp) {
		printf("Reached stack bottom\n");
		return;
	}

	size = fp - *(unsigned long*)fp;
	memdump((unsigned char*)fp, size);

	dump_stackframe((unsigned char*)*(unsigned long*)fp);
}

void myHandle(int signo, siginfo_t *info, void *ptr)
{
	struct sigcontext *pt_reg = &((ucontext_t*)ptr)->uc_mcontext;
	void *array[10];
	char ** strings;
	size_t size;
	int i;

	/* show register info */
	printf("\nRegister context:\n");
	printf(" Memory location which caused fault: %08x\n", pt_reg->fault_address);
	printf(" Exception instruction: %08x\n", pt_reg->arm_pc); 
	printf(" Link register: %08x\n", pt_reg->arm_lr);
	printf(" CPSR register: %08x\n", pt_reg->arm_cpsr);
	printf(" r0 = %08x, r1 = %08x, r2 = %08x, r3 = %08x\n", 
			pt_reg->arm_r0, pt_reg->arm_r1, pt_reg->arm_r2, pt_reg->arm_r3);
	printf(" r4 = %08x, r5 = %08x, r6 = %08x, r7 = %08x\n", 
			pt_reg->arm_r4, pt_reg->arm_r5, pt_reg->arm_r6, pt_reg->arm_r7);
	printf(" r8 = %08x, r9 = %08x, r10 = %08x, fp = %08x\n", 
			pt_reg->arm_r8, pt_reg->arm_r9, pt_reg->arm_r10, pt_reg->arm_fp);
	printf(" ip = %08x, sp = %08x, lr = %08x, pc = %08x\n", 
			pt_reg->arm_ip, pt_reg->arm_sp, pt_reg->arm_lr, pt_reg->arm_pc);

	/* show stack info*/
	printf("\nStart dumpping stack:\n");
	dump_stackframe(pt_reg->arm_fp);

	/* show function tracking list */
	array[0] = (void*)pt_reg->arm_pc;
	array[1] = (void*)pt_reg->arm_lr;
	size = backtrace(array+2, 8);
	size += 2;
	strings = backtrace_symbols(array, size);
	printf("\nFunction tracking list:\n");
	for (i = 0; i < size; i++) {
		printf("  %s\n", strings[i]);
	}
	free(strings);
	strings = NULL;

	exit(signo);
}

int ab02=1;
void (*q)(int);

extern void abc(int c);

void ab2(int c2)
{
	memset(0x0b, 0, 10);
}

int main(int argc, char**argv)
{
	struct sigaction act;

	if (argc != 2)
		return -11;

	switch (argv[1][0])
	{
		case 'd':
		{
			act.sa_sigaction = myHandle;
			act.sa_flags = SA_SIGINFO;
			sigaction(SIGSEGV, &act, NULL);
			abc(ab02);
		}
		case 't':
		{
			act.sa_sigaction = myHandle;
			act.sa_flags = SA_SIGINFO;
			sigaction(SIGSEGV, &act, NULL);
			q = NULL;
			q(1);
		}
		default:
			return -33;
	}
			
	printf("Hello, autoconfig.\n");
	return 0;
}

