/*! Skandhas class */
#ifndef SKANDHAS_H
#define SKANDHAS_H

#include "bugBase.h"

class Skandhas {
public:
	/*! construct function */
	Skandhas();
	/*! add bugs */
	void add(BugBase* bug);
	/*! remove bugs */
	void rm(string name);
	/*! get bugs */
	BugBase* get(string name);
	/*! show help */
	void help(void);

	/*! the list contain all  bugs */
	list<BugBase*> bugs;
};

#endif /* SKANDHAS_H */

