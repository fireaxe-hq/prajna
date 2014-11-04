#include "prajna.h"
#include "include/exc_info.h"
#include "include/exc_trigger.h"

int ab02=1;

extern void abc(int c);

void ab2(int c2)
{
	memset(0x0b, 0, 10);
}

int main(int argc, char**argv)
{
	if (argc != 2) {
		printf("Please input a bug type.\n");
		return -11;
	}

	if (argv[1][1] != 0) { 
		if (argv[1][1] == 'd') {
			switch (argv[1][0]) {
				case 'd':
				case 't':
				{
					exc_install(argv[1][0]);
					break;
				}
				default:
					break;
			}
		} else {
			printf("unknown debug type\n");
			exit -22;
		}
	}

	switch (argv[1][0])
	{
		case 'd':
		{
			abc(ab02);
			break;
		}
		case 't':
		{
			void (*q)(int);

			q = NULL;
			q(1);
			break;
		}
		default:
			perror("unknown bug type\n");
			return -33;
	}
			
	printf("Hello, autoconfig.\n");
	return 0;
}

