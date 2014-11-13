#include "prajna.h"
#include "common.h"
#include <execinfo.h>

void dump_mem(unsigned char *base, unsigned long size)
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

void dump_stackframe(unsigned long fp)
{
	unsigned long size;

	if (0 == fp) {
		printf("Reached stack bottom\n");
		return;
	}

	size = fp - *(unsigned long*)fp;
	dump_mem((unsigned char*)fp, size);

	dump_stackframe((unsigned long)*(unsigned long*)fp);
}

void dump_register(struct sigcontext *pt_reg)
{
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
}

void dump_trace(void *array[], int size)
{
	int i;
	char ** strings;

	strings = backtrace_symbols(array, size);
	printf("\nFunction tracking list:\n");
	for (i = 0; i < size; i++) {
		printf("  %s\n", strings[i]);
	}
	free(strings);
}

