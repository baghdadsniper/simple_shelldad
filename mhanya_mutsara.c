#include "shell.h"

/**
 * exec_lines -
 *
 * @datash:
 * Return:
 */
int exec_lines(data_shell *datash)
{
	int (*builtin)(data_shell *datash);

	if (datash->args[0] == NULL)
		return (1);

	builtin = get_builtins(datash->args[0]);

	if (builtin != NULL)
		return (builtin(datash));

	return (cmd_execs(datash));
}
