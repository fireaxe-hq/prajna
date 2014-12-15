#ifndef TOPAPPLET_H
#define TOPAPPLET_H

#include "appletBase.h"

/*! class */
class TopApplet : public AppletBase {
public:
	/*! construct function */
	TopApplet():AppletBase("top") {}
	int trigger(char argc, char **argv);
	/*! show help */
	void help(void);
};

typedef struct top_info {
	proc_sts_t *p;
	unsigned long proc_cpu_ratio;
} top_info;

#define SHOW_NUM 30
#define MAX_PROC_NUM 1000

#endif /* TOPAPPLET_H */

