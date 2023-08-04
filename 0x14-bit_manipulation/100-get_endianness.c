#include "main.h"

/**
 * get_endianness - checks the endianness of the system
 * Return: 0 if big endian, 1 if little endian.
 */

int get_endianness() 
{
	int num = 1;
    	char *byte_ptr = (char *)&num;

    	return ((int)(*byte_ptr));
}
