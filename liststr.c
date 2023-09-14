#include "shell.h"

/**
 * add_nodes - adds a node to the start of the list
 * @head: address of pointer to head node
 * @strs: strs field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_nodes(list_t **head, const char *strs, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memsets((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (strs)
	{
		new_head->strs = _strsdup(strs);
		if (!new_head->strs)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_nodes_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @strs: strs field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *add_nodes_end(list_t **head, const char *strs, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memsets((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (strs)
	{
		new_node->strs = _strsdup(strs);
		if (!new_node->strs)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_lists_strss - prints only the strs element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_lists_strss(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->strs ? h->strs : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * delete_node_at_indexs - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_indexs(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->strs);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->strs);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_lists - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_lists(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->strs);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
