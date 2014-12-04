/*! Paramita class */
#ifndef PARAMIA_H
#define PARAMIA_H

#include "appletBase.h"

class Paramita {
public:
	/*! construct function */
	Paramita();
	/*! add */
	void add(AppletBase* bug);
	/*! remove bugs */
	void rm(string name);
	/*! get */
	AppletBase* get(string name);
	/*! show help */
	void help(void);

	/*! the list contain all applets */
	list<AppletBase*> applets;
};

#endif /* PARAMIA_H */

