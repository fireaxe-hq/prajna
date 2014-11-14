/*! provide useful command to get info of system.
 * USR_CMD is used to transfer command to kernel.
 * use 'help' parameter to see what commands are supproted.
 */

#include "prajna.h"
#include <getopt.h>

using namespace std;

#define NAME_MAX_LEN 20

/*! Transfer command from userspace to kernel. */
struct USR_CMD {
	char name[NAME_MAX_LEN]; /*!< the command */
	unsigned long para[8]; /*!< parameters, maximum 8 parameters are available. */
};

static void help_info(void)
{
	printf("help info:\n");
	printf("Usage: paramita <cmd>\n");
	printf("execute cmd.\n");
	printf("\ncommand type:\n");
	printf("  md base size\n");
}

int main(int argc, char**argv)
{
	int fd, i;
	struct USR_CMD cmd;
	unsigned long ret;

	if (argc < 2) {
		cout<<"too few para:"<<argc<<endl;
		help_info();
		return (-1);
	}
	if (argc > 6) {
		cout<<"too many para:"<<argc<<endl;
		help_info();
		return (-1);
	}

	fd = open("/dev/prajna_k", O_RDWR);
	if (fd == -1) {
		printf("error open\n");
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
		printf("cmd is invalid!\n");
		help_info();
		exit (-3);
	}
	
	close(fd);
	return 0;
}

