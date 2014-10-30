#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include "prajna.h"

#define NAME_MAX_LEN 20

struct USR_CMD {
	char name[NAME_MAX_LEN];
	unsigned long para[8];
};

int CmdParser(struct USR_CMD *cmd, int argc, char *argv[])
{
	ssize_t size;
	int i;

}

int main(int argc, char**argv)
{
	int fd, i;
	struct USR_CMD cmd;
	unsigned long ret;

	if (argc < 2) {
		printf("too few para:%d\n", argc);
		return (-1);
	}
	if (argc > 6) {
		printf("too many para:%d\n", argc);
		return (-1);
	}

	fd = open("/dev/prajna_k", O_RDWR);
	if (fd == -1) {
		perror("error open\n");
		exit (-2);
	}

	memset(&cmd, 0, sizeof(struct USR_CMD));
	strcpy(cmd.name, argv[1]);

	for (i = 2; i < argc; i++) {
		if (('0' == *(argv[i])) && ('x' == *(argv[i]+1))) {
			// hex parse
			sscanf(argv[i], "0x%x", &cmd.para[i-2]);
		} else if ('"' == *(argv[i])) {
			// string parse
		} else {
			cmd.para[i-2] = atoi(argv[i]);
		}
	}

	ret = write(fd, &cmd, sizeof(cmd));
	if (ERR_CMD_INVALID == ret) {
		perror("cmd is invalid!\n");
		exit (-3);
	}
	
	close(fd);
	return 0;
}

