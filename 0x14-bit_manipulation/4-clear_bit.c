#include "main.h"

/**
 * clear_bit - sets the value of a bit to 0 at a given index
 * @n: pointer of an unsigned long int
 * @index: index of the bit
 * Return: 1 if it worked, -1 if not.
 */

int clear_bit(unsigned long int *n, unsigned int index) 
{
	if (index >= sizeof(unsigned long int) * 8) 
        	return (-1);

    	*n &= ~(1UL << index);
    	return (1);
}

