#include "shell.h"

/**
 * _erratois - converts a strsing to an integer
 * @s: the strsing to be converted
 * Return: 0 if no numbers in strsing, converted number otherwise
 *       -1 on error
 */
int _erratois(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++; /* TODO: why does this make main return 255? */
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_errors - prints an error message
 * @info: the parameter & return info strsuct
 * @estrs: strsing containing specified error type
 * Return: 0 if no numbers in strsing, converted number otherwise
 *        -1 on error
 */
void print_errors(info_t *info, char *estrs)
{
	_iputs(info->fname);
	_iputs(": ");
	print_ds(info->line_count, STDERR_FILENO);
	_iputs(": ");
	_iputs(info->argv[0]);
	_iputs(": ");
	_iputs(estrs);
}

/**
 * print_ds - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_ds(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _iputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_numbers - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: strsing
 */
char *convert_numbers(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do
	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the strsing to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
