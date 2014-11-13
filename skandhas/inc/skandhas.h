#ifndef SKANDHAS_H
#define SKANDHAS_H

#include "bugBase.h"

class Skandhas {
public:
	Skandhas();
	void add(BugBase* bug);
	void rm(string name);
	BugBase* get(string name);
	void help(void);

	list<BugBase*> bugs;
};

#endif /* SKANDHAS_H */

