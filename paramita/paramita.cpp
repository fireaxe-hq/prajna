#include "prajna.h"
#include "paramita.h"

Paramita::Paramita()
{
	this->applets.clear();
	this->name = "paramita";
}

void Paramita::add(AppletBase* applet)
{
	this->applets.push_back(applet);
}

void Paramita::rm(string name)
{
	list <AppletBase*>::iterator it;
#if 0
	for (it = this->applets.begin(); it != this->applets.end(); it++ ) {
		if (it->match(name)) {
			this->applets.remove(*it->self());
			delete(it->self());
		}
	}
#endif
}

AppletBase* Paramita::get(string name)
{
	list <AppletBase*>::iterator it;

	for (it = this->applets.begin(); it != this->applets.end(); it++ ) {
		AppletBase *p = *it;
		if (p->match(name))
			return p;
	}

	return NULL;
}

void Paramita::install(char *path)
{
	list <AppletBase*>::iterator it;
	string oldpath(path);

	oldpath += this->get_name();
	for (it = this->applets.begin(); it != this->applets.end(); it++ ) {
		AppletBase *p = *it;
		string newpath(path);

		newpath  += p->get_name();
		symlink(oldpath.c_str(), newpath.c_str());
	}
	this->help();
}

void Paramita::help()
{
	list <AppletBase*>::iterator it;
	int output_width = 80;
	int len = 0;
	bool first_applet = true;

	printf("\nCurrently defined functions:\n");
	for (it = this->applets.begin(); it != this->applets.end(); it++ ) {
		AppletBase *p = *it;
		if (!first_applet) {
			printf(", ");
		}
		
		first_applet = false;
		len += p->get_name().size() + 2;
		if (len > output_width) {
			printf("\n");
			first_applet = true;
			len = p->get_name().size() + 2;
		}
		printf("%s", p->get_name().c_str());
	}
	printf("\n");
}

