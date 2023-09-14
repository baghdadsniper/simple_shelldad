#include "shell.h"

/**
 * interactives - returns true if shell is interactives mode
 * @info: strsuct address
 *
 * Return: 1 if interactives mode, 0 otherwise
hello
*/
int interactives(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delims - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter strsing
 * Return: 1 if true, 0 if false
hello
*/
int is_delims(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - checks for alphabetic character
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
hello
*/

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atois - converts a strsing to an integer
 *@s: the strsing to be converted
 *Return: 0 if no numbers in strsing, converted number otherwise
hello
*/

int _atois(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
