#include <stdint.h>

/**
 * Question 1 - Byte Sum
 * Write a function that calculates the sum of four 8-bit numbers stored in a
 * 32-bit unsigned integer using SWAR.
 *
 * Consider the 32-bit input as follows:
 * | byte3 | byte2 | byte1 | byte0 |
 *
 * Your function should have the following prototype:
 * uint32_t byte_sum(uint32_t n);
 *
 * Rules:
 * - Do not use loops. (for, while etc.)
 * - Do not extract each byte into separate variables.
 * - Only bitwise and arithmetic operations are allowed.
 * - Perform the calculation in parallel within a single register.
 *
 * Example:
 * uint32_t x = 0x01020304;
 *
 * byte0 = 0x04
 * byte1 = 0x03
 * byte2 = 0x02
 * byte3 = 0x01
 * The sum is: 1 + 2 + 3 + 4 = 10
 **/
uint32_t
byte_sum(uint32_t n)
{
	n = (n & 0x00FF00FF) + ((n >> 8) & 0x00FF00FF);
	n = (n & 0x0000FFFF) + (n >> 16);
	return (n);
}

