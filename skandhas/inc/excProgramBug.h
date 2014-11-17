/*! program exception */
#ifndef EXCPROGRAMBUG_H
#define EXCPROGRAMBUG_H

#include "bugBase.h"

/*! program exception bug class */
class ExcProgramBug : public BugBase {
public:
	/*! construct function */
	ExcProgramBug():BugBase("program") {}
	/*! trigger program access exception bug */
	void trigger(void);
	/*! if debug function is enabled */
	bool dbg_en(bool val);
	/*! show help */
	void help(void);
};

#endif /* EXCPROGRAMBUG_H */

