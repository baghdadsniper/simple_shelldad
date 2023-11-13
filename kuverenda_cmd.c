#include "shell.h"

/**
 * read_lines -
 *
 * @i_eof:
 * Return:
 */
char *read_lines(int *i_eof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&input, &bufsize, stdin);

	return (input);
}
