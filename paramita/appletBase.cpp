#include "prajna.h"
#include "appletBase.h"

AppletBase::AppletBase(string name)
{
   this->name = "p_" + name;
}

bool AppletBase::match(string str)
{
	return (str == this->name) ? true : false;
}

