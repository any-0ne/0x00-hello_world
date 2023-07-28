#include "lists.h"

/**
 * print_list - prints a list_t list
 * @h: singly linked list
 * Return: number of elements in the list
 */

size_t print_list(const list_t *myList)
{
	size_t nbElem;

	nbElem = 0;
	while (myList != NULL)
	{
		if (myList->str == NULL)
			printf("[%d] %s\n", 0, "(nil)");
		else
			printf("[%d] %s\n", myList->len, myList->str);
		myList = myList->next;
		nbElem++;
	}
	
	return (nbElem);
}
