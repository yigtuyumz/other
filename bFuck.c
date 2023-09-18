// the brainfuck compiler...
#include "./utils/include/utils.h" /* extended utilities */
#include <unistd.h>                /* for write */
#include <stdlib.h>                /* for malloc */
#include <string.h>                /* for memset */
#define BUFF_SZ 30000
/*
> 	işaretçiyi bir sonraki hücreye kaydır.
< 	işaretçiyi bir önceki hücreye kaydır.
+ 	işaretçinin bulunduğu hücredeki baytı 1 arttır.
- 	işaretçinin bulunduğu hücredeki baytı 1 azalt.
. 	işaretçinin bulunduğu hücredeki baytı standart çıktı birimine yaz.
, 	standart girdi biriminden bir baytlık girdi al ve bunu işaretçinin
		bulunduğu hücreye yaz.
[ 	eğer işaretçinin bulunduğu hücrenin değeri sıfırsa,
		] karakterinden sonraki komuta atla.
] 	eğer işaretçinin bulunduğu hücrenin değeri sıfır değilse,
		önceki [ karakterinden bir sonraki komuta atla.
*/

void
compile(char *c)
{
	int i = 0;
	char *ptr = (char *) malloc(sizeof(char) * BUFF_SZ);

	if (ptr == NULL) {
		write(STDERR_FILENO, "Malloc fails.\n", 14);
		exit(EXIT_FAILURE);
	}
	memset(ptr, 0, sizeof(char) * BUFF_SZ);

	int cellPos = 0;
	int stackPush = 0;
	while (*(c + i)) {
		if (*(c + i) == '+') {
			++(*(ptr + cellPos));
		} else if (*(c + i) == '-') {
			--(*(ptr + cellPos));
		} else if (*(c + i) == '.') {
			if (*(ptr+cellPos) == 0) {
				write(STDOUT_FILENO, "NULL\n", 5);
			} else {
				write(STDOUT_FILENO, (ptr + cellPos), 1);
			}
		} else if (*(c + i) == '>') {
			cellPos++;
			if (cellPos == BUFF_SZ - 1) {
				write(STDERR_FILENO, ">Out of bounds.\n", 16);
				exit(EXIT_FAILURE);
			}
		} else if (*(c + i) == '<') {
			cellPos--;
			if (cellPos < 0) {
				write(STDERR_FILENO, "<Out of bounds.\n", 16);
				exit(EXIT_FAILURE);
			}
		// TODO read single char from STDIN
		} else if (*(c + i) == ',') {

		// TODO stack implementation. push, pop, stack pointer(sp) etc.
		} else if (*(c + i) == '[') {
			stackPush++;
		}
		i++;
	}
	free(ptr);
}

int
main(int argc, char *argv[])
{
	if (argc == 1) {
		write(STDERR_FILENO, "No arg.\n", 8);
		exit(EXIT_FAILURE);
	} else {
		utils_putstr(STDOUT_FILENO, "Input: ");
		utils_putstr(STDOUT_FILENO, argv[1]);
		compile(argv[1]);
		exit(EXIT_SUCCESS);
	}
}
