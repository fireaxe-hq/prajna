#ifndef COMMON_H
#define COMMON_H

#include "prajna.h"
#include <execinfo.h>
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

#endif /* COMMON_H */

