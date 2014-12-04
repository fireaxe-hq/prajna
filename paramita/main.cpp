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
	AppletBase *applet;

	applet_name = argv[0];
	if(applet_name[0] == '-')
		applet_name++;
	applet_name = strrchr(applet_name, '/');
	applet_name++;

	if ((applet = paramita->get(applet_name)) != NULL) {
		if ((argc == 2) && (0 == strncmp(argv[1], "help", 5)))
			applet->help();
		else
			applet->trigger(argc, argv);
	} else {
		paramita->help();
	}

	return 0;
}

