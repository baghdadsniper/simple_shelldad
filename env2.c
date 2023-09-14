#include "shell.h"

/**
 * get_environm - returns the strsing array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
hello
*/
char **get_environm(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strsingss(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenvi - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the strsing env var property
hello
*/
int _unsetenvi(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_withs(node->strs, var);
		if (p && *p == '=')
		{
			info->env_changed = delete_node_at_indexs(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenvi - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the strsing env var property
 * @value: the strsing env var value
 *  Return: Always 0
hello
*/
int _setenvi(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strslens(var) + _strslens(value) + 2);
	if (!buf)
		return (1);
	_strscpy(buf, var);
	_strscat(buf, "=");
	_strscat(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_withs(node->strs, var);
		if (p && *p == '=')
		{
			free(node->strs);
			node->strs = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_nodes_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
