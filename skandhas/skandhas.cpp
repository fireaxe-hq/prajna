#include "prajna.h"
#include "skandhas.h"

Skandhas::Skandhas()
{
	this->bugs.clear();
}

void Skandhas::add(BugBase* bug)
{
	this->bugs.push_back(bug);
}

void Skandhas::rm(string name)
{
	list <BugBase*>::iterator it;
#if 0
	for (it = this->bugs.begin(); it != this->bugs.end(); it++ ) {
		if (it->match(name)) {
			this->bugs.remove(*it->self());
			delete(it->self());
		}
	}
#endif
}

BugBase* Skandhas::get(string name)
{
	list <BugBase*>::iterator it;

	for (it = this->bugs.begin(); it != this->bugs.end(); it++ ) {
		BugBase *p = *it;
		if (p->match(name))
			return p;
	}

	return NULL;
}

void Skandhas::help()
{
	list <BugBase*>::iterator it;

	for (it = this->bugs.begin(); it != this->bugs.end(); it++ ) {
		BugBase *p = *it;
		p->help();
	}
}

