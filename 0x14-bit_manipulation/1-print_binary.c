#include "main.h"
#include <stdio.h>

/**
 * binary_to_uint - convert a binary number to an unsigned int
 * @b: char string which contains binary number
 * Return: converted number or 0 if b==NULL or if there is a string b that is not 0 or 1
 */


unsigned int binary_to_uint(const char *b)
{
	int len;
	unsigned int total, power;

	if (b == NULL)
		return (0);

	for (len = 0; b[len]; len++)
	{
		if (b[len] != '0' && b[len] != '1')
			return (0);
	}

	for (power = 1, total = 0, len--; len >= 0; len--, power *= 2)
	{
		if (b[len] == '1')
			total += power;
	}

	return (total);
}
