#ifndef MDAPPLET_H
#define MDAPPLET_H

#include "appletBase.h"

/*! memory dump applet*/
class MdApplet : public AppletBase {
public:
	/*! construct function */
	MdApplet():AppletBase("md") { }
	/*! trigger the md applet */
	int trigger(char argc, char **argv);
	/*! show help */
	void help(void);
};

#endif /* MDAPPLET_H */

