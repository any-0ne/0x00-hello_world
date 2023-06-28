#include "main.h"

/**
 * swap_int - swaps 2 numbers.
 * @a: a.
 * @b: b.
 * Return: void.
 */
void swap_int(int *a, int *b)
{
	int swp = *a;
	*a = *b;
	*b = swp;
}
