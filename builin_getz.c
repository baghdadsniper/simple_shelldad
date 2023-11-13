#include "shell.h"

/**
 * get_builtins -
 * @cmd:
 * Return:
 */
int (*get_builtins(char *cmd))(data_shell *)
{
	builtin_t builtin[] = {
		{"env", _env},
		{"exit", exit_shells},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv},
		{"cd", cd_shells},
		{"help", get_helps},
		{NULL, NULL}};
	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (_strcomp(builtin[i].name, cmd) == 0)
			break;
	}
	return (builtin[i].f);
}
