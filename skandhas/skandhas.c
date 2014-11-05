#include "prajna.h"
#include <getopt.h>
#include "include/exc_info.h"
#include "include/exc_trigger.h"

static struct option long_options[] = {
	{"help", no_argument, NULL, 'h'}, 
	{"error", required_argument, NULL, 'e'}, 
	{"debug", no_argument, NULL, 'd'}, 
	{NULL, 0, NULL, 0}
};

static char *short_opts = "he:d";

void help_info(void)
{
	printf("help info:\n");
}

int main(int argc, char**argv)
{
	int opt;
	char err_type[50];
	char dbg_enable = 0;
	char get_para = 0;

	if (argc < 2) {
		printf("Please input a parameter.\n");
		help_info();
		return -11;
	}

	while ((opt = getopt_long(argc, argv, short_opts, long_options, NULL)) != -1) {
		switch (opt) {
			case 'h':
				help_info();
				return 0;
			case 'e':
				strcpy(err_type, optarg);
				break;
			case 'd':
				dbg_enable = 1;
				break;
		}
		get_para = 1;
	}

	if (get_para == 0) {
		printf("Please input invalide parameter...\n");
		help_info();
		return -22;
	}

	if (dbg_enable == 1) { 
		if ((0 == strcmp(err_type, "data")) || 
			(0 == strcmp(err_type, "text"))) {
			exc_install(err_type[0]);
		}
	}

	if (0 == strcmp(err_type, "data")) {
	   trig_exc_mem();
	} else if (0 == strcmp(err_type, "text")) {
		trig_exc_text();
	} else {
		printf("Unknown error err_type.\n");
		help_info();
		return -44;
	}

	return 0;
}

