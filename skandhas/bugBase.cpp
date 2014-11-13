#include "prajna.h"
#include "bugBase.h"

BugBase::BugBase(string name)
{
   this->name = name;
   this->isDbg = false;
}

bool BugBase::match(string str)
{
	return (str == this->name) ? true : false;
}

