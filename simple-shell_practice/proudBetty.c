#include <stdio.h>

/**
 * main - A beauty of a code that passes betty check
 * Return: Always return
 */

int main(void)
{
	int i, j;

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			printf("(%d, %d) ", i, j);
		}
		printf("n");
	}

	return (0);
}

