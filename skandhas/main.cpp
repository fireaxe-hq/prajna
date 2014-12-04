#include "prajna.h"
#include <getopt.h>
#include "skandhas.h"

static struct option long_options[] = {
	{"help", no_argument, NULL, 'h'}, 
	{"bug", required_argument, NULL, 'b'}, 
	{"debug", no_argument, NULL, 'd'}, 
	{NULL, 0, NULL, 0}
};

static string short_opts("hb:d");

static Skandhas *skandhas = new Skandhas;

bool add_bug(void *bug)
{
	skandhas->add((BugBase*)bug);
	return true;
}

static void help_info(void)
{
	printf("help info:\n");
	printf("Usage: skandha -b bug_type [-d]\n");
	printf("Trigger different kinds of bugs, and show debug information if '-d' is used.\n");
	printf("\nbug type:\n");
	skandhas->help();
}

int main(int argc, char**argv)
{
	int opt;
	string bug_type;
	bool dbg_enable = false;
	char get_para = 0;
	BugBase *bug;

	if (argc < 2) {
		printf("Please input a parameter...\n");
		help_info();
		return -11;
	}

	while ((opt = getopt_long(argc, argv, short_opts.data(), long_options, NULL)) != -1) {
		switch (opt) {
			case 'h':
				help_info();
				return 0;
			case 'b':
				bug_type =  optarg;
				break;
			case 'd':
				dbg_enable = true;
				break;
		}
		get_para = 1;
	}

	if (get_para == 0) {
		printf("Please input invalide parameter...\n");
		help_info();
		return -22;
	}

	if ((bug = skandhas->get(bug_type)) != NULL) {
		bug->dbg_en(dbg_enable);
		bug->trigger();
	} else {
		printf("Unknown error bug_type...\n");
		help_info();
		return -44;
	}
	
	return 0;
}

