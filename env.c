#include "shell.h"

/**
 * _yourenv - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _yourenv(info_t *info)
{
	print_lists_strss(info->env);
	return (0);
}

/**
 * _bringenv - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_bringenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_withs(node->strs, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _yoursetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _yoursetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_iputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenvi(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _yourunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _yourunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_iputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenvi(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_nodes_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
