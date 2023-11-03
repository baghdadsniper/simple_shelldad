#include "shell.h"

/**
 * read_line - 
 *
 * @i_eof: 
 * Return: 
 */
char *read_line(int *i_eof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&input, &bufsize, stdin);

	return (input);
}
