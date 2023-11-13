#include "shell.h"

/**
 * get_errors -
 * @datash:
 * @eval:
 * Return:
 */
int get_errors(data_shell *datash, int eval)
{
	char *error;

	switch (eval)
	{
	case -1:
		error = errors_env(datash);
		break;
	case 126:
		error = error_path_1262(datash);
		break;
	case 127:
		error = errors_not_found(datash);
		break;
	case 2:
		if (_strcomp("exit", datash->args[0]) == 0)
			error = error_exit_shellss(datash);
		else if (_strcomp("cd", datash->args[0]) == 0)
			error = errors_get_cd(datash);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlenth(error));
		free(error);
	}

	datash->status = eval;
	return (eval);
}
