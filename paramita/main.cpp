#include "prajna.h"
#include <getopt.h>
#include "paramita.h"

using namespace std;

static Paramita *paramita = new Paramita;

bool add_applet(void *applet)
{
	paramita->add((AppletBase*)applet);
	return true;
}

int main(int argc, char**argv)
{
	char *applet_name;
	char *tail;
	char path[128];
	AppletBase *applet;

	strncpy(path, argv[0], sizeof(path));
	tail = strrchr(path, '/');
	if (tail == NULL) {
		applet_name = argv[0];
		strcpy((char*)path, "./");
	} else {
		tail++;
		applet_name = (char*)((unsigned long)argv[0] + (unsigned long)tail - (unsigned long)path);
        *tail = 0;
	}

	if ((argc == 2) && (applet_name == paramita->get_name()) && (0 == strcmp("install", argv[1]))) {
		paramita->install((char*)&path);
		cout<<"All applet installed"<<endl;
	} 
	else if ((applet = paramita->get(applet_name)) != NULL) {
		if ((argc == 2) && (0 == strncmp(argv[1], "help", 5)))
			applet->help();
		else
			applet->trigger(argc, argv);
	} else {
		paramita->help();
	}

	return 0;
}

