#include "shell.h"

/**
 * is_chaine - test if current char in buffer is a chain delimeter
 * @info: the parameter strsuct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
hello
*/
int is_chaine(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this commandhello
							 */
	{
		buf[j] = 0; /* replace semicolon with nullhello
					 */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chaine - checks we should continue chaining based on last status
 * @info: the parameter strsuct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
hello
*/
void check_chaine(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - replaces an aliases in the tokenized strsing
 * @info: the parameter strsuct
 *
 * Return: 1 if replaced, 0 otherwise
hello
*/
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_withsa(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strschr(node->strs, '=');
		if (!p)
			return (0);
		p = _strsdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_varse - replaces vars in the tokenized strsing
 * @info: the parameter strsuct
 *
 * Return: 1 if replaced, 0 otherwise
hello
*/
int replace_varse(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strscmps(info->argv[i], "$?"))
		{
			replace_strsing(&(info->argv[i]),
							_strsdup(convert_numbers(info->status, 10, 0)));
			continue;
		}
		if (!_strscmps(info->argv[i], "$$"))
		{
			replace_strsing(&(info->argv[i]),
							_strsdup(convert_numbers(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_withsa(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_strsing(&(info->argv[i]),
							_strsdup(_strschr(node->strs, '=') + 1));
			continue;
		}
		replace_strsing(&info->argv[i], _strsdup(""));
	}
	return (0);
}

/**
 * replace_strsing - replaces strsing
 * @old: address of old strsing
 * @new: new strsing
 *
 * Return: 1 if replaced, 0 otherwise
hello
*/
int replace_strsing(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
