#include "shell.h"

/**
 * strcats_cd -
 * @datash:
 * @msg:
 * @error:
 * @ver_str:
 * Return:
 */
char *strcats_cd(data_shell *datash, char *msg, char *error, char *ver_str)
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
 * errors_get_cd -
 * @datash:
 * Return:
 */
char *errors_get_cd(data_shell *datash)
{
	int length, len_id;
	char *error, *ver_str, *msg;

	ver_str = aux_itoas(datash->counter);
	if (datash->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlenth(datash->args[1]);
	}

	length = _strlenth(datash->av[0]) + _strlenth(datash->args[0]);
	length += _strlenth(ver_str) + _strlenth(msg) + len_id + 5;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(ver_str);
		return (NULL);
	}

	error = strcats_cd(datash, msg, error, ver_str);

	free(ver_str);

	return (error);
}

/**
 * errors_not_found -
 * @datash:
 * Return:
 */
char *errors_not_found(data_shell *datash)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = aux_itoas(datash->counter);
	length = _strlenth(datash->av[0]) + _strlenth(ver_str);
	length += _strlenth(datash->args[0]) + 16;
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
 * error_exit_shellss -
 * @datash:
 *
 * Return:
 */
char *error_exit_shellss(data_shell *datash)
{
	int length;
	char *error;
	char *ver_str;

	ver_str = aux_itoas(datash->counter);
	length = _strlenth(datash->av[0]) + _strlenth(ver_str);
	length += _strlenth(datash->args[0]) + _strlenth(datash->args[1]) + 23;
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
