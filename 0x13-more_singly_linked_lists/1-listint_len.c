#include "lists.h"

/**
 * print_listint - prints elements of a list
 * @h: head of a list
 * Return: numbers of nodes.
 */

size_t print_listint(const listint_t *h)
{
	size_t nodes = 0;

	while (h != NULL)
	{
		h = h->next;
		nodes++;
	}
	return (nodes);
}
