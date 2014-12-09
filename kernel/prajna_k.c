/** prajna module
 * this module shall be installed into kernel
 */

#include "prajna_k.h"

static void memdump(u32 para[8])
{
	int i;
	char *base;
	u32 size = para[1];
	char buff[60];
	
	printk(KERN_INFO" memdump %x, %x", para[0], para[1]);
	base = (char*)ioremap(para[0], size);
	if (NULL == base) {
		printk(KERN_ERR"the address 0x%08x is unaccessable.", para[0]);
		return;
	}

	for (buff[0] = 0, i = 0; i < size; i++) {
		if (i%(4*4) == 0) {
			if (i != 0)
				printk(KERN_ALERT"%s\n", buff);
			buff[0] = 0;
			snprintf(buff, sizeof(buff) - 1, "%08x:",  (u32)(para[0] + i));
		}
		if (i%4 == 0)
			snprintf(buff, sizeof(buff) - 1, "%s ", buff);

		snprintf(buff, sizeof(buff) - 1, "%s%02x", buff, *(base + i));
	}
	printk(KERN_ALERT"\n");

	iounmap(base);
}

static ssize_t myDev_read(struct file *f, char __user *addr, size_t size, loff_t *off)
{

	return 0;
}

/*! all commands and their respective handle functions are linked by this structure */
struct CMD_LIST {
	char *name; /*!< command name */
	void (*ptr)(u32 para[8]); /*!< pointer to handler */
};

struct CMD_LIST cmdList[] = {
	{"p_md", memdump}, 
	{NULL, NULL}
};

static ssize_t myDev_write(struct file *f, const char __user *addr, size_t size, loff_t *off)
{
	void (*ptr)(u32 para[8]);
	struct USR_CMD cmd;
	int i;

	// get cmd from user space to kernel space;
	if (0 != copy_from_user((char*)&cmd, addr, sizeof(struct USR_CMD)))
		return -123;
	/*printk(KERN_INFO"prajna_k: show command: %s-%d", cmd.name, sizeof(cmd.name));*/

	// get function ptr by name;
	for (i = 0; cmdList[i].ptr != NULL; i++) {
		if (0 == strcmp(cmd.name, cmdList[i].name)) {
			ptr = cmdList[i].ptr;
			break;
		}
	}

	if (NULL == cmdList[i].ptr) {
		printk(KERN_ERR"prajna_k: error command: %s", cmd.name);
		return (ERR_CMD_INVALID);
	}

	// run function ptr;
	ptr(cmd.para);

	return 0;
}

static int myDev_open(struct inode *inode, struct file *file)
{
	return 0;
}

static const struct file_operations myDev_fops = {
	.owner = THIS_MODULE,
	.open = myDev_open,
	.read = myDev_read,
	.write = myDev_write,
};

struct cdev *dev;

static int __init my_init(void)
{
	dev_t devNum;
	if (alloc_chrdev_region(&devNum, 0, 1, "prajna_k")) {
		printk(KERN_ERR"allocate device number failed");
		return -1;
	}
	
	dev = cdev_alloc();
	if (dev == NULL) {
		printk(KERN_ERR"error create device");
		return -1;
	}

	cdev_init(dev, &myDev_fops);

	if (0 > cdev_add(dev, devNum, 1)) {
		printk(KERN_ERR"error init device");
		return -1;
	}

	return 0;
}

static void __exit my_exit(void)
{
	cdev_del(dev);
	unregister_chrdev_region(MKDEV(12,1), 1);
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Marco Hao");

