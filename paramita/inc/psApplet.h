#ifndef PSAPPLET_H
#define PSAPPLET_H

#include "appletBase.h"

/*! show all process info */
class PsApplet : public AppletBase {
public:
	/*! construct function */
	PsApplet():AppletBase("ps") {}
	int trigger(char argc, char **argv);
	/*! show help */
	void help(void);
};

#endif /* PSAPPLET_H */

