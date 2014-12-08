#ifndef _H
#define _H

#include "appletBase.h"

/*! class */
class TmpApplet : public AppletBase {
public:
	/*! construct function */
	TmpApplet():AppletBase("tmp") {}
	int trigger(char argc, char **argv);
	/*! show help */
	void help(void);
};

#endif /* _H */

