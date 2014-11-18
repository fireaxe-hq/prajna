/*! */
#ifndef _H
#define _H

#include "bugBase.h"

/*! bug class */
class TmpBug : public BugBase {
public:
	/*! construct function */
	TmpBug():BugBase("tmp") {}
	/*! trigger tmp bug */
	void trigger(void);
	/*! if debug function is enabled */
	bool dbg_en(bool val);
	/*! show help */
	void help(void);
};

#endif /* _H */

