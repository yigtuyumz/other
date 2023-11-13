// Brainfuck Interpreter - CLI
// This program reads the input from STDIN, not from a file or something!!

#include <unistd.h>                     /* for write */

#define BUFF_SZ 30000

void
compile(char *c)
{
	int i = 0;
	int cellpos = 0;
	int count;
	char ptr[BUFF_SZ] = { 0 };

	while (*(c + i)) {
		if (*(c + i) == '+') {
			(*(ptr + cellpos))++;
		} else if (*(c + i) == '-') {
			(*(ptr + cellpos))--;
		} else if (*(c + i) == '>') {
			cellpos++;
			if (cellpos >= BUFF_SZ) {
				write(STDERR_FILENO, "> Out of bounds.\n", 17);
				return ;
			}
		} else if (*(c + i) == '<') {
			cellpos--;
			if (cellpos < 0) {
				write(STDERR_FILENO, "< Out of bounds.\n", 17);
				return ;
			}
		} else if (*(c + i) == '.') {
			write(STDOUT_FILENO, (ptr + cellpos), 1);
// !        } else if (*(c + i) == ',') {
//              ! functions like read or getchar, gets the ENTER key too,
//              ! because of terminal. (I suppose..) So that, I didn't
//              ! implement this feature.
		} else if (*(c + i) == '[') {
			if (*(ptr + cellpos) == 0) {
				count = 1;
				while (count > 0) {
					i++;
					if (*(c + i) == '[') {
						count++;
					} else if (*(c + i) == ']') {
						count--;
					}
				}
			}
		} else if (*(c + i) == ']') {
			if (*(ptr + cellpos) != 0) {
				count = 1;
				while (count > 0) {
					i--;
					if (*(c + i) == ']') {
						count++;
					} else if (*(c + i) == '[') {
						count--;
					}
				}
			}
		}
		i++;
	}
}

int
main(int argc, char *argv[])
{
	if (argc == 1) {
		write(STDERR_FILENO, "No arg.\n", 8);
		return (1);
	}
	compile(argv[1]);

	return (0);
}
