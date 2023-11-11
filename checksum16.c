#include "/root/utils.h"
#include <stdio.h>

void
print_byte(__uint8_t byte, __uint8_t len)
{
	printf("Value: %04X decimal: %u\n", byte, byte);
	for (int i = ((8 * len) - 1); i >= 0; i--) {
		printf("%d", GETBIT(byte, i));
		if (i % 8 == 0) {
			printf(" ");
		}
	}
	printf("\n");
}

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


int
main(int argc, char const *argv[])
{
	__uint16_t data[] = {0x4500, 0x0073, 0x1234, 0x4000, 0x4011, 0xc0a8, 0x0001, 0xc0a8, 0x00c7};
	printf("%04X\n", checksum16(data, 9));
	printf("%04X\n", validate_checksum16(data, 9, checksum16(data, 9)));
	return 0;
}
