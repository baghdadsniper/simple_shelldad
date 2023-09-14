#include "shell.h"

/**
 * _yourhistorye - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _yourhistorye(info_t *info)
{
	print_lists(info->history);
	return (0);
}

/**
 * unset_aliasee - sets alias to strsing
 * @info: parameter strsuct
 * @strs: the strsing alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_aliasee(info_t *info, char *strs)
{
	char *p, c;
	int ret;

	p = _strschr(strs, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_indexs(&(info->alias),
								get_node_indexs(info->alias, node_starts_withsa(info->alias, strs, -1)));
	*p = c;
	return (ret);
}

/**
 * set_aliase - sets alias to strsing
 * @info: parameter strsuct
 * @strs: the strsing alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_aliase(info_t *info, char *strs)
{
	char *p;

	p = _strschr(strs, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_aliasee(info, strs));

	unset_aliasee(info, strs);
	return (add_nodes_end(&(info->alias), strs, 0) == NULL);
}

/**
 * print_aliase - prints an alias strsing
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_aliase(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strschr(node->strs, '=');
		for (a = node->strs; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _youralias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _youralias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_aliase(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strschr(info->argv[i], '=');
		if (p)
			set_aliase(info, info->argv[i]);
		else
			print_aliase(node_starts_withsa(info->alias, info->argv[i], '='));
	}

	return (0);
}
