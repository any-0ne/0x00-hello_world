#include "variadic_functions.h"

/**
 * print_numbers - prints numbers
 * @separator: string to be printed between numbers
 * @n: number of ints
 * Return: void.
 */

void print_numbers(const char *separator, const unsigned int n, ...)
{
	va_list myList;
	unsigned int i;

	va_start(myList, n);

	for (i = 0; i < n; i++)
	{
		printf("%d", va_arg(myList, int));
		if (separator && i < n - 1)
			printf("%s", separator);
	}

	printf("\n");
	va_end(myList);
}

