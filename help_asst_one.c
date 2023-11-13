#include "shell.h"

/**
 * get_helps -
 * @datash:
 * Return:
 */
int get_helps(data_shell *datash)
{

	if (datash->args[1] == 0)
		aux_helps_general();
	else if (_strcomp(datash->args[1], "setenv") == 0)
		aux_helps_setenv();
	else if (_strcomp(datash->args[1], "env") == 0)
		aux_helps_env();
	else if (_strcomp(datash->args[1], "unsetenv") == 0)
		aux_helps_unsetenv();
	else if (_strcomp(datash->args[1], "help") == 0)
		aux_helps();
	else if (_strcomp(datash->args[1], "exit") == 0)
		aux_helps_exit();
	else if (_strcomp(datash->args[1], "cd") == 0)
		aux_helps_cd();
	else if (_strcomp(datash->args[1], "alias") == 0)
		aux_helps_alias();
	else
		write(STDERR_FILENO, datash->args[0],
			  _strlenth(datash->args[0]));

	datash->status = 0;
	return (1);
}
