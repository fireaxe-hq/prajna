#include "prajna_k.h"

#define MYDEV_NAME "myDev"
#define NAME_MAX_LEN 20

struct USR_CMD {
	char name[NAME_MAX_LEN];
	u32 para[8];
};

static struct device *my_dev;

#if 0
int CmdParser(struct USR_CMD *cmd, int argc, char *argv[])
{
	ssize_t size;
	int i;

	if (argc < 2) {
		printf("too few para:%d\n", argc);
		return (-1);
	}
	if (argc > 6) {
		printf("too many para:%d\n", argc);
		return (-1);
	}

	memset(cmd, 0, sizeof(struct USR_CMD));
	strcpy(cmd->name, argv[1]);

	for (i = 2; i < argc; i++) {
		if (('0' == *(argv[i])) && ('x' == *(argv[i]+1))) {
			// hex parse
			sscanf(argv[i], "0x%x", &cmd->para[i-2]);
		} else if ('"' == *(argv[i])) {
			// string parse
		} else {
			cmd->para[i-2] = atoi(argv[i]);
		}
	}
}
#endif

static void memdump(u32 para[4])
{
	int i;
	char *base;
	u32 size = para[1];

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

static ssize_t myDev_read(struct file *f, const char __user *addr, size_t size, loff_t *off)
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
	copy_from_user((char*)&cmd, addr, sizeof(struct USR_CMD));
	printk(KERN_INFO"show command: %s", cmd.name);

	// get function ptr by name;
	for (i = 0; cmdList[i].ptr == NULL; i++) {
		if (0 == strcmp(cmd.name, cmdList[i].name)) {
			ptr = cmdList[i].ptr;
			break;
		}
	}

	if (NULL != cmdList[i].ptr) {
		printk(KERN_ERR"error command: %s", cmd.name);
		return (-1);
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

	dev = cdev_alloc();
	if (dev == NULL) {
		printk(KERN_ERR"error create device\n");
		return -1;
	}

	cdev_init(dev, &myDev_fops);

	if (0 > cdev_add(dev, 12, 1)) {
		printk(KERN_ERR"error init device\n");
		return -1;
	}

	return 0;
}

static void __exit my_exit(void)
{
	cdev_del(dev);
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Marco Hao");

