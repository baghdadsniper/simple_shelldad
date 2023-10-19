#include "shell.h"

/**
 * _myhistory2 - displays the history2 list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory2(info_t *info)
{
	print_list2(info->history2);
	return (0);
}

/**
 * unset_alias2 - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias2(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr2(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index2(&(info->alias),
								get_node_index2(info->alias, node_starts_with2(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias2 - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias2(info_t *info, char *str)
{
	char *p;

	p = _strchr2(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias2(info, str));

	unset_alias2(info, str);
	return (add_node_end2(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias2 - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias2(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr2(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar2(*a);
		_putchar2('\'');
		_puts2(p + 1);
		_puts2("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias2 - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias2(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc2 == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias2(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv2[i]; i++)
	{
		p = _strchr2(info->argv2[i], '=');
		if (p)
			set_alias2(info, info->argv2[i]);
		else
			print_alias2(node_starts_with2(info->alias, info->argv2[i], '='));
	}

	return (0);
}
