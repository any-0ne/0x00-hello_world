#include "lists.h"

/**
 * free_listint2 - frees a  list
 * @head: head of a list
 * Return: void.
 */
void free_listint2(listint_t **head)
{
	listint_t *temp;
	listint_t *h;

	if (head != NULL)
	{
		h = *head;
		while ((temp = h) != NULL)
		{
			h = h->next;
			free(temp);
		}
		*head = NULL;
	}
}
