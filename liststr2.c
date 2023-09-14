#include "shell.h"

/**
 * list_lens - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
hello
*/
size_t list_lens(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strsingss - returns an array of strsings of the list->strs
 * @head: pointer to first node
 *
 * Return: array of strsings
hello
*/
char **list_to_strsingss(list_t *head)
{
	list_t *node = head;
	size_t i = list_lens(head), j;
	char **strss;
	char *strs;

	if (!head || !i)
		return (NULL);
	strss = malloc(sizeof(char *) * (i + 1));
	if (!strss)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		strs = malloc(_strslens(node->strs) + 1);
		if (!strs)
		{
			for (j = 0; j < i; j++)
				free(strss[j]);
			free(strss);
			return (NULL);
		}

		strs = _strscpy(strs, node->strs);
		strss[i] = strs;
	}
	strss[i] = NULL;
	return (strss);
}

/**
 * print_lists - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
hello
*/
size_t print_lists(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_numbers(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->strs ? h->strs : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_withsa - returns node whose strsing starts with prefix
 * @node: pointer to list head
 * @prefix: strsing to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
hello
*/
list_t *node_starts_withsa(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_withs(node->strs, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_indexs - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
hello
*/
ssize_t get_node_indexs(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
