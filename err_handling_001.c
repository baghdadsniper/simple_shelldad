#include "shell.h"

/**
 * strcat_cd - 
 * @datash: 
 * @msg: 
 * @error: 
 * @ver_str: 
 * Return: 
 */
char *strcat_cd(data_shell *datash, char *msg, char *error, char *ver_str)
{
	char *illegal_flag;

	_strcopy(error, datash->av[0]);
	_strdog(error, ": ");
	_strdog(error, ver_str);
	_strdog(error, ": ");
	_strdog(error, datash->args[0]);
	_strdog(error, msg);
	if (datash->args[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = datash->args[1][1];
		illegal_flag[2] = '\0';
		_strdog(error, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		_strdog(error, datash->args[1]);
	}

	_strdog(error, "\n");
	_strdog(error, "\0");
	return (error);
}

/**
 * error_get_cd - 
 * @datash: 
 * Return: 
 */
char *error_get_cd(data_shell *datash)
{
	int length, len_id;
	char *error, *ver_str, *msg;

	ver_str = aux_itoa(datash->counter);
	if (datash->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlen(datash->args[1]);
	}

	length = _strlen(datash->av[0]) + _strlen(datash->args[0]);
	length += _strlen(ver_str) + _strlen(msg) + len_id + 5;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}

	error = strcat_cd(datash, msg, error, ver_str);

	free(ver_str);

	return (error);
}

/**
 * error_not_found - 
 * @datash:
 * Return: 
 */
char *error_not_found(data_shell *datash)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = aux_itoa(datash->counter);
	length = _strlen(datash->av[0]) + _strlen(ver_str);
	length += _strlen(datash->args[0]) + 16;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_strcopy(error, datash->av[0]);
	_strdog(error, ": ");
	_strdog(error, ver_str);
	_strdog(error, ": ");
	_strdog(error, datash->args[0]);
	_strdog(error, ": not found\n");
	_strdog(error, "\0");
	free(ver_str);
	return (error);
}

/**
 * error_exit_shell -
 * @datash: 
 *
 * Return: 
 */
char *error_exit_shell(data_shell *datash)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = aux_itoa(datash->counter);
	length = _strlen(datash->av[0]) + _strlen(ver_str);
	length += _strlen(datash->args[0]) + _strlen(datash->args[1]) + 23;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}
	_strcopy(error, datash->av[0]);
	_strdog(error, ": ");
	_strdog(error, ver_str);
	_strdog(error, ": ");
	_strdog(error, datash->args[0]);
	_strdog(error, ": Illegal number: ");
	_strdog(error, datash->args[1]);
	_strdog(error, "\n\0");
	free(ver_str);

	return (error);
}
