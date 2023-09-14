#include "shell.h"

/**
 *_iputs - prints an input strsing
 * @strs: the strsing to be printed
 *
 * Return: Nothing
 */
void _iputs(char *strs)
{
	int i = 0;

	if (!strs)
		return;
	while (strs[i] != '\0')
	{
		_iputchar(strs[i]);
		i++;
	}
}

/**
 * _iputchar - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _iputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfwd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfwd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *_putsfwd - prints an input strsing
 * @strs: the strsing to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfwd(char *strs, int fd)
{
	int i = 0;

	if (!strs)
		return (0);
	while (*strs)
	{
		i += _putfwd(*strs++, fd);
	}
	return (i);
}
