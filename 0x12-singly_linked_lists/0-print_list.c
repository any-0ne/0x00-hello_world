#include "lists.h"

/**
 * print_list - prints a list_t list
 * @h: singly linked list
 * Return: number of elements in the list
 */

size_t print_list(const list_t *myList)
{
	size_t nb;
	list_t copyList = myList;

	nb = 0;
	while (copyList != NULL)
	{
		if (copyList->str == NULL)
			printf("[%d] %s\n", 0, "(nil)");
		else
			printf("[%d] %s\n", copyList->len, copyList->str);
		copyList = copyList->next;
		nb++;
	}
	return (nb);
}
