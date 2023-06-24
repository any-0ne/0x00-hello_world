#include "main.h"

/**
 * _isdigit - checks if c is a  number between 0 to 9.
 * Return: 1 if is a number (0 to 9), 0 in otherwise.
 */
int _isdigit(int c)
{
	if (c >= 48 && c <= 57)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
