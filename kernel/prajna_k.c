#include "prajna_k.h"

#define MYDEV_NAME "myDev"
#define NAME_MAX_LEN 20

struct USR_CMD {
	char name[NAME_MAX_LEN];
	u32 para[8];
};

static void memdump(u32 para[4])
{
	int i;
	char *base;
	u32 size = para[1];

	printk(KERN_INFO" memdump %x, %x\n", para[0], para[1]);
	base = (char*)ioremap(para[0], size);

	for (i = 0; i < size; i++) {
		if ((i%4 == 0) && i)
			printk(" ");
		if (i%(4*4) == 0)
			printk("\n%08x: ", (u32)(para[0] + i));
		printk("%02x", *(base + i));
	}

	printk("\n");
	iounmap(base);
}

static ssize_t myDev_read(struct file *f, char __user *addr, size_t size, loff_t *off)
{

	return 0;
}

struct CMD_LIST {
	char *name;
	void *ptr;
};

struct CMD_LIST cmdList[] = {
	{"dump", memdump}, 
	{NULL, NULL}
};

static ssize_t myDev_write(struct file *f, const char __user *addr, size_t size, loff_t *off)
{
	void (*ptr)(u32 para[4]);
	struct USR_CMD cmd;
	int i;

	// get cmd from user space to kernel space;
	if (0 != copy_from_user((char*)&cmd, addr, sizeof(struct USR_CMD)))
		return -123;
	printk(KERN_INFO"prajna_k: show command: %s-%d\n", cmd.name, sizeof(cmd.name));

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
		printk(KERN_ERR"allocate device number failed\n");
		return -1;
	}
	
	dev = cdev_alloc();
	if (dev == NULL) {
		printk(KERN_ERR"error create device\n");
		return -1;
	}

	cdev_init(dev, &myDev_fops);

	if (0 > cdev_add(dev, devNum, 1)) {
		printk(KERN_ERR"error init device\n");
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

