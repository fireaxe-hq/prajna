/*! AppletBase class, all other applets classes shall be based on it */
#ifndef APPLETBASE_H
#define APPLETBASE_H 

/* base class of all applets */
class AppletBase {
public:
	/*! construct function */
	AppletBase(string name);
	/*! get name */
	string get_name(void) const { return this->name; }
	/*! check if match with this object */
	bool match(string str);
	/*! trigger */
	virtual int trigger(char argc, char **argv) = 0;
	/*! show help */
	virtual void help(void) = 0;
private:
	string name; /*!< applet name */
};

#endif /* APPLETBASE_H */

