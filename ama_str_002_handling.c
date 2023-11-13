#include "shell.h"

/**
 * _strdump -
 * @s:
 * Return:
 */
char *_strdump(const char *s)
{
	char *new;
	size_t len;

	len = _strlenth(s);
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	_memcpys(new, s, len + 1);
	return (new);
}

/**
 * _strlenth -
 * @s:
 * Return:
 */
int _strlenth(const char *s)
{
	int len;

	for (len = 0; s[len] != 0; len++)
	{
	}
	return (len);
}

/**
 * cmp_cars -
 * @str:
 * @delim:
 *
 * Return:
 */
int cmp_cars(char str[], const char *delim)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; str[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (str[i] == delim[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}

/**
 * _strlok -
 * @str:
 * @delim:
 *
 * Return:
 */
char *_strlok(char str[], const char *delim)
{
	static char *splitted, *str_end;
	char *str_start;
	unsigned int i, bool;

	if (str != NULL)
	{
		if (cmp_cars(str, delim))
			return (NULL);
		splitted = str;
		i = _strlenth(str);
		str_end = &str[i];
	}
	str_start = splitted;
	if (str_start == str_end)
		return (NULL);

	for (bool = 0; *splitted; splitted++)
	{

		if (splitted != str_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;

		for (i = 0; delim[i]; i++)
		{
			if (*splitted == delim[i])
			{
				*splitted = '\0';
				if (splitted == str_start)
					str_start++;
				break;
			}
		}
		if (bool == 0 && *splitted)
			bool = 1;
	}
	if (bool == 0)
		return (NULL);
	return (str_start);
}

/**
 * _isdigital -
 *
 * @s:
 * Return:
 */
int _isdigital(const char *s)
{
	unsigned int i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] < 48 || s[i] > 57)
			return (0);
	}
	return (1);
}
