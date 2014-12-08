/** header file for prajna kernel module */
#ifndef PRAJNA_K_H
#define PRAJNA_K_H

#include <linux/module.h>  /* for modules */
#include <linux/fs.h>      /* file_operations */
#include <linux/uaccess.h> /* copy_(to,from)_user */
#include <linux/init.h>          /* module_init, module_exit */
#include <linux/slab.h>    /* kmalloc, kfree */
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/io.h>

#define ERR_CMD_INVALID 0x12340001

#define MYDEV_NAME "myDev"
#define NAME_MAX_LEN 20

/*! Transfer command from userspace to kernel. */
struct USR_CMD {
	char name[NAME_MAX_LEN]; /*!< the command */
	unsigned int para[8]; /*!< parameters, maximum 8 parameters are available. */
};

#endif /* PRAJNA_K_H */

