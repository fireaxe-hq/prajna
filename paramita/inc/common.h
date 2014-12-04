#ifndef COMMON_H
#define COMMON_H

#include <signal.h>

#ifdef __cplusplus
extern "C"
{
#endif


#define NAME_MAX_LEN 20

/*! Transfer command from userspace to kernel. */
struct USR_CMD {
	char name[NAME_MAX_LEN]; /*!< the command */
	unsigned long para[8]; /*!< parameters, maximum 8 parameters are available. */
};

#ifdef __cplusplus
}
#endif

/*! add applet object into paramita object */
bool add_applet(void *applet);

/*! install applet into paramita */
#define applet_install(x) \
	x __tmp_##x; \
	void __applet_con_##x() __attribute__((constructor)); \
	void __applet_con_##x() \
	{ \
		add_applet(&__tmp_##x); \
	}

	/*! unstall applet from paramita */
#define applet_unstall(x) \
	void __applet_des_##x() __attribute__((destructor)); \
	void __applet_des_##x() \
	{ \
	}

#endif /* COMMON_H */

