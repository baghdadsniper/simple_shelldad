#include "shell.h"

/**
 * repeated_chars -
 * @input:
 * @i:
 * Return:
 */
int repeated_chars(char *input, int i)
{
	if (*(input - 1) == *input)
		return (repeated_chars(input - 1, i + 1));

	return (i);
}

/**
 * error_sep_op -
 * @input:
 * @i:
 * @last:
 * Return:
 */
int error_sep_op(char *input, int i, char last)
{
	int count;

	count = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (error_sep_op(input + 1, i + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			count = repeated_chars(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			count = repeated_chars(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	return (error_sep_op(input + 1, i + 1, *input));
}

/**
 * first_chars -
 * @input:
 * @i:
 * Return:
 */
int first_chars(char *input, int *i)
{
	for (*i = 0; input[*i]; *i += 1)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;

		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * print_syntax_errors -
 * @datash:
 * @input:
 * @i:
 * @bool:
 * Return:
 */
void print_syntax_errors(data_shell *datash, char *input, int i, int bool)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	if (input[i] == ';')
	{
		if (bool == 0)
			msg = (input[i + 1] == ';' ? ";;" : ";");
		else
			msg = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		msg = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		msg = (input[i + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\"unexpected\n";
	counter = aux_itoas(datash->counter);
	length = _strlenth(datash->av[0]) + _strlenth(counter);
	length += _strlenth(msg) + _strlenth(msg2) + _strlenth(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcopy(error, datash->av[0]);
	_strdog(error, ": ");
	_strdog(error, counter);
	_strdog(error, msg2);
	_strdog(error, msg);
	_strdog(error, msg3);
	_strdog(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}

/**
 * check_syntax_errors -
 * @datash:
 * @input:
 * Return:
 */
int check_syntax_errors(data_shell *datash, char *input)
{
	int begin = 0;
	int f_char = 0;
	int i = 0;

	f_char = first_chars(input, &begin);
	if (f_char == -1)
	{
		print_syntax_errors(datash, input, begin, 0);
		return (1);
	}

	i = error_sep_op(input + begin, 0, *(input + begin));
	if (i != 0)
	{
		print_syntax_errors(datash, input, begin + i, 1);
		return (1);
	}

	return (0);
}
