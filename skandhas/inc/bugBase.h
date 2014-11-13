#ifndef BUGBASE_H
#define BUGBASE_H 

class BugBase {
public:
	BugBase(string name);
	string get_name(void) const { return this->name; }
	BugBase* self(void) { return this; }
	bool match(string str);
	virtual void trigger(void) = 0;
	virtual bool dbg_en(bool val) = 0;
	virtual void help(void) = 0;
private:
	string name;
	bool isDbg;
};

#endif /* BUGBASE_H */

