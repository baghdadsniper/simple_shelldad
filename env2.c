#include "shell.h"

/**
 * get_environ2 - returns the string array copy of our environ2
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **get_environ2(info_t *info)
{
	if (!info->environ2 || info->env_changed2)
	{
		info->environ2 = list_to_strings2(info->env);
		info->env_changed2 = 0;
	}

	return (info->environ2);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with2(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed2 = delete_node_at_index2(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed2);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen2(var) + _strlen2(value) + 2);
	if (!buf)
		return (1);
	_strcpy2(buf, var);
	_strcat2(buf, "=");
	_strcat2(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_with2(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed2 = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end2(&(info->env), buf, 0);
	free(buf);
	info->env_changed2 = 1;
	return (0);
}
