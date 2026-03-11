#include <stdint.h>

/**
 * Question 2 - Byte-Wise Popcount
 * Write a function that counts the number of 1 bits in each byte of a
 * 32-bit unsigned integer and returns the results in the same byte positions
 * inside a 32-bit unsigned integer using SWAR.
 *
 * Consider the 32-bit input as four bytes:
 * | byte3 | byte2 | byte1 | byte0 |
 *
 * Each byte in the output should contain the number of set bits (1s) in the
 * corresponding byte of the input.
 *
 * Your function should have the following prototype:
 * uint32_t popcount(uint32_t x);
 *
 * Rules:
 * - Do not use loops. (for, while etc.)
 * - Do not use built-in popcount functions.
 * - Do not write separate operations for each byte (no manual unrolling).
 * - Only bitwise, shift, and arithmetic operations are allowed.
 * - Perform the calculation in parallel within a single register using SWAR.
 *
 * Example:
 * uint32_t x = 0xF0A50C03;
 *
 * byte0 = 0x03 = 0b00000011 -> 2
 * byte1 = 0x0C = 0b00001100 -> 2
 * byte2 = 0xA5 = 0b10100101 -> 4
 * byte3 = 0xF0 = 0b11110000 -> 4
 *
 * The output should be: 0x04040202
 **/
uint32_t
popcount(uint32_t x)
{
	/* count bits in 2-bit groups */
	x = x - ((x >> 1) & 0x55555555);

	/* sum 2-bit groups into 4-bit groups */
	x = (x & 0x33333333) + ((x >> 2) & 0x33333333);

	/* sum nibbles into bytes */
	x = (x + (x >> 4)) & 0x0F0F0F0F;

	return (x);
}

