#include "prajna.h"
#include "common.h"
#include <execinfo.h>
#include "mdApplet.h"

int MdApplet::trigger(char argc, char **argv)
{
	int fd;
	struct USR_CMD cmd;
	unsigned long ret;

	if (argc != 3) {
		printf("invalid para: %d\n", argc);
		this->help();
		return (-1);
	}

	fd = open("/dev/prajna_k", O_RDWR);
	if (fd == -1) {
		printf("error open\n");
		exit (-2);
	}

	memset(&cmd, 0, sizeof(struct USR_CMD));
	strcpy(cmd.name, this->get_name().c_str());
	for (int i = 1; i < argc; i++) {
		if (('0' == *(argv[i])) && ('x' == *(argv[i]+1))) {
			// hex parse
			sscanf(argv[i], "0x%x", &cmd.para[i-1]);
		} else if ('"' == *(argv[i])) {
			// string parse
		} else {
			cmd.para[i-1] = atoi(argv[i]);
		}
	}

	ret = write(fd, &cmd, sizeof(cmd));
	if (ERR_CMD_INVALID == ret) {
		printf("cmd is invalid!\n");
		this->help();
		exit (-3);
	}
	
	close(fd);
	return 0;
}

void MdApplet::help(void)
{
	printf("help info:\n");
	printf("Usage: paramita <cmd>\n");
	printf("execute cmd.\n");
	printf("\ncommand type:\n");
	printf("  md base size\n");
}

applet_install(MdApplet)
applet_unstall(MdApplet)

