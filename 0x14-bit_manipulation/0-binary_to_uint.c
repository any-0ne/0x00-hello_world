#include <stdio.h>

/* binary_to_uint - convert bin to u int
 * @b: binary input
 * Return: converted integer.
 */

unsigned int binary_to_uint(const char *b)
{
	int i;
	unsigned int decimal = 0;
	
	if (!b)
		return (0);

	for (i=0; b[i] != '\0'; i++)
	{
		if (b[i] != '0' && b[i] != '1')
			return(0);
		if (b[i] == '1')
			decimal = (decimal << 1) | 1;
		else if (b[i] == '0')
			decimal = decimal << 1;
	}
	return (decimal);
}
