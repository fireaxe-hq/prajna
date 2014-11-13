#ifndef EXCPROGRAMBUG_H
#define EXCPROGRAMBUG_H

#include "bugBase.h"

class ExcProgramBug : public BugBase {
public:
	ExcProgramBug():BugBase("program") {}
	void trigger(void);
	bool dbg_en(bool val);
	void help(void);
};

#endif /* EXCPROGRAMBUG_H */

