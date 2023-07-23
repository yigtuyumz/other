#include <unistd.h>

void
my_putchar(char c)
{
	write(1, &c, 1);
}
/*
 * 0xFFFFFFFFFFFFFFFF
 */
void
print_bits(size_t val, short size)
{
	if (size != 0) {
		print_bits(val >> 1, --size);
		my_putchar((val & 1) + 48);
	}
}
