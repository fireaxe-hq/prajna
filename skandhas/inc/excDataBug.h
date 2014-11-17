/*! data access exception */
#ifndef EXCDATABUG_H
#define EXCDATABUG_H

#include "bugBase.h"

/*! data accee exception bug class */
class ExcDataBug : public BugBase {
public:
	/*! construct function */
	ExcDataBug():BugBase("data") { }
	/*! trigger data access exception bug */
	void trigger(void);
	/*! if debug function is enabled */
	bool dbg_en(bool val);
	/*! show help */
	void help(void);
};

#endif /* EXCDATABUG_H */

