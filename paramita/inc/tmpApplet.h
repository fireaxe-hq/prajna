/*! */
#ifndef _H
#define _H

#include "appletBase.h"

/*! class */
class tmpApplet : public BugBase {
public:
	/*! construct function */
	tmpApplet():AppletBase("tmp") {}
	/*! trigger tmp */
	void trigger(void);
	/*! show help */
	void help(void);
};

#endif /* _H */

