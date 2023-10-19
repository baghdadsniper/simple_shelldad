#include "shell.h"

/**
 * is_chain2 - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain2(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type2 = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type2 = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type2 = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain2 - checks we should continue chaining based on last status2
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain2(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type2 == CMD_AND)
	{
		if (info->status2)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type2 == CMD_OR)
	{
		if (!info->status2)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias2 - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias2(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with2(info->alias2, info->argv2[0], '=');
		if (!node)
			return (0);
		free(info->argv2[0]);
		p = _strchr2(node->str, '=');
		if (!p)
			return (0);
		p = _strdup2(p + 1);
		if (!p)
			return (0);
		info->argv2[0] = p;
	}
	return (1);
}

/**
 * replace_vars2 - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars2(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv2[i]; i++)
	{
		if (info->argv2[i][0] != '$' || !info->argv2[i][1])
			continue;

		if (!_strcmp2(info->argv2[i], "$?"))
		{
			replace_string2(&(info->argv2[i]),
							_strdup2(convert_number2(info->status2, 10, 0)));
			continue;
		}
		if (!_strcmp2(info->argv2[i], "$$"))
		{
			replace_string2(&(info->argv2[i]),
							_strdup2(convert_number2(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with2(info->env, &info->argv2[i][1], '=');
		if (node)
		{
			replace_string2(&(info->argv2[i]),
							_strdup2(_strchr2(node->str, '=') + 1));
			continue;
		}
		replace_string2(&info->argv2[i], _strdup2(""));
	}
	return (0);
}

/**
 * replace_string2 - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string2(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
