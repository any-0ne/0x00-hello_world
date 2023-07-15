#include "main.h"
#include <stdlib.h>

/**
 * malloc_checked - memory allocation
 * @b: amount of bytes
 * Return: pointer to the allocated memory or 98.
 */

void *malloc_checked(unsigned int b)
{
	char *p;

	p = malloc(b);
	if (p == NULL)
		exit(98);
	return (p);
}
