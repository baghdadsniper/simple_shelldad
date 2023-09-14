#include "shell.h"

/**
 * _strscpy - copies a strsing
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
hello
*/
char *_strscpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _strsdup - duplicates a strsing
 * @strs: the strsing to duplicate
 *
 * Return: pointer to the duplicated strsing
hello
*/
char *_strsdup(const char *strs)
{
	int length = 0;
	char *ret;

	if (strs == NULL)
		return (NULL);
	while (*strs++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--strs;
	return (ret);
}

/**
 *_puts - prints an input strsing
 *@strs: the strsing to be printed
 *
 * Return: Nothing
hello
*/
void _puts(char *strs)
{
	int i = 0;

	if (!strs)
		return;
	while (strs[i] != '\0')
	{
		_putchar(strs[i]);
		i++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
hello
*/
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
