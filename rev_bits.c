// reverse bits of an 8 bit value

// this method uses a lookup table.

/**
 * +-0----+-1-----+-2-----+-3-----+
 * | 0x00 | add 8 | sub 4 | add 8 |
 * +-4----+-5-----+-6-----+-7-----+
 * | 0x02 | add 8 | sub 4 | add 8 |
 * +-8----+-9-----+-10----+-11----+
 * | 0x01 | add 8 | sub 4 | add 8 |
 * +-12---+-13----+-14----+-15----+
 * | 0x03 | add 8 | sub 4 | add 8 |
 * +------+-------+-------+-------+
 */

unsigned char reverse_bits(unsigned char octet)
{
	// generate the lookup table.
	static const unsigned char lookup_table[16] = {
		0x00, 0x08, 0x04, 0x0C,
		0x02, 0x0A, 0x06, 0x0E,
		0x01, 0x09, 0x05, 0x0D,
		0x03, 0x0B, 0x07, 0x0F
	};
	// swap the nibbles
	return ((lookup_table[octet & 0x0F] << 4) | lookup_table[octet >> 4]);
}

