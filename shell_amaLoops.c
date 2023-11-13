#include "shell.h"

/**
 * without_comments -
 * @in:
 * Return:
 */
char *without_comments(char *in)
{
	int i, up_to;

	up_to = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}
			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				up_to = i;
		}
	}

	if (up_to != 0)
	{
		in = _reallocs(in, i, up_to + 1);
		in[up_to] = '\0';
	}

	return (in);
}

/**
 * shell_loops -
 * @datash:
 *
 * Return:
 */
void shell_loops(data_shell *datash)
{
	int loop, i_eof;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "^-^ ", 4);
		input = read_lines(&i_eof);
		if (i_eof != -1)
		{
			input = without_comments(input);
			if (input == NULL)
				continue;

			if (check_syntax_errors(datash, input) == 1)
			{
				datash->status = 2;
				free(input);
				continue;
			}
			input = rep_vars(input, datash);
			loop = split_commandos(datash, input);
			datash->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}
