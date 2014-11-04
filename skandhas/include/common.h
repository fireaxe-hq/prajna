#ifndef COMMON_H
#define COMMON_H

#include "prajna.h"
#include <execinfo.h>
#include <signal.h>

void dump_mem(unsigned char *base, unsigned long size);
void dump_stackframe(unsigned long fp);
void dump_register(struct sigcontext *pt_reg);
void dump_trace(void *array[], int size);

#endif /* COMMON_H */

