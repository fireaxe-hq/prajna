/*! Paramita class */
#ifndef PARAMIA_H
#define PARAMIA_H

#include "appletBase.h"

class Paramita {
public:
	/*! construct function */
	Paramita();
	/*! install all applets as soft-link */
	void install(char *path);
	/*! add */
	void add(AppletBase* bug);
	/*! remove bugs */
	void rm(string name);
	/*! get name */
	string get_name() const { return this->name; }
	/*! get */
	AppletBase* get(string name);
	/*! show help */
	void help(void);

	/*! the list contain all applets */
	list<AppletBase*> applets;
private:
	string name;
};

#endif /* PARAMIA_H */

