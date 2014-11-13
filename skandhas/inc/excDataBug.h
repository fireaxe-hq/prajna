#ifndef EXCDATABUG_H
#define EXCDATABUG_H

#include "bugBase.h"

class ExcDataBug : public BugBase {
public:
	ExcDataBug():BugBase("data") { }
	void trigger(void);
	bool dbg_en(bool val);
	void help(void);
};

#endif /* EXCDATABUG_H */

