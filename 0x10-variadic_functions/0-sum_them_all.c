#include "variadic_functions.h"

/**
 * sum_them_all - returns the sum of all args
 * @n: number of the args
 * Return: sum.
 */

int sum_them_all(const unsigned int n, ...)
{
	va_list myList;
	unsigned int i;
	int sum = 0;

	if (n == 0)
		return (0);

	va_start(myList, n);

	for (i = 0; i < n; i++)
		sum += va_arg(myList, int);

	va_end(myList);

	return (sum);
}
