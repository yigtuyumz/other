/*
 * #include "utils.h"
 *
 * void
 * print_byte(__uint8_t byte, __uint8_t len)
 * {
 * 
 * 	utils_putstr(STDOUT_FILENO, "Value: ");
 * 	utils_putnbr(STDOUT_FILENO, (__uint8_t) byte);
 * 	for (int i = ((8 * len) - 1); i >= 0; i--) {
 * 		utils_putnbr(STDOUT_FILENO, GETBIT(byte, i));
 * 		if (i % 8 == 0) {
 * 			utils_putchar(STDOUT_FILENO, ' ');
 * 		}
 * 	}
 * 	utils_putchar(STDOUT_FILENO, '\n');
 * }
 */

__uint16_t
checksum16(__uint16_t lst[], __uint8_t len)
{
	__uint32_t s = 0;

	while (len--) {
		s += lst[len];
	}

	__uint16_t l;
	while (s > 0xFFFF) {
		l = s >> 16;
		s &= 0x0000FFFF;
		s += l;
	}

	return (~s);
}

__uint16_t
validate_checksum16(__uint16_t lst[], __uint8_t len, __uint16_t checksum)
{
	__uint32_t s = checksum;

	while (len--) {
		s += lst[len];
	}

	__uint16_t l = 0;
	while (s > 0xFFFF) {
		l = s >> 16;
		s &= 0x0000FFFF;
		s += l;
	}

	if (s == 0xFFFF) {
		return (0);
	}

	return (1);
}

