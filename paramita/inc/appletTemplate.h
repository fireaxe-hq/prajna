/*! */
#ifndef _H
#define _H

#include "appletBase.h"

/*! class */
class TmpApplet : public BugBase {
public:
	/*! construct function */
	TmpApplet():AppletBase("tmp") {}
	/*! trigger tmp */
	void trigger(void);
	/*! show help */
	void help(void);
};

#endif /* _H */

