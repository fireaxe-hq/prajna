/*! BugBase class, all other bugs classes shall be based on it */
#ifndef BUGBASE_H
#define BUGBASE_H 

/* base class of all bugs */
class BugBase {
public:
	/*! construct function */
	BugBase(string name);
	/*! get name of bug */
	string get_name(void) const { return this->name; }
	/*! check if match with this object */
	bool match(string str);
	/*! trigger this bug */
	virtual void trigger(void) = 0;
	/*! if debug function is enabled */
	virtual bool dbg_en(bool val) = 0;
	/*! show help */
	virtual void help(void) = 0;
private:
	string name; /*!< bug name */
	bool isDbg; /*!< if debug function is enabled */
};

#endif /* BUGBASE_H */

