#include "shell.h"

/**
 * errors_env -
 * @datash:
 * Return:
 */
char *errors_env(data_shell *datash)
{
	int length;
	char *error;
	char *ver_str;
	char *msg;

	ver_str = aux_itoas(datash->counter);
	msg = ": Unable to add/remove from environment\n";
	length = _strlenth(datash->av[0]) + _strlenth(ver_str);
	length += _strlenth(datash->args[0]) + _strlenth(msg) + 4;
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
	_strdog(error, msg);
	_strdog(error, "\0");
	free(ver_str);

	return (error);
}
/**
 * error_path_1262 -
 * @datash:
 *
 * Return:
 */
char *error_path_1262(data_shell *datash)
{
	int length;
	char *ver_str;
	char *error;

	ver_str = aux_itoas(datash->counter);
	length = _strlenth(datash->av[0]) + _strlenth(ver_str);
	length += _strlenth(datash->args[0]) + 24;
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
	_strdog(error, ": Permission denied\n");
	_strdog(error, "\0");
	free(ver_str);
	return (error);
}
