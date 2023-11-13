#include "shell.h"

/**
 * free_datas -
 * @datash:
 * Return:
 */
void free_datas(data_shell *datash)
{
	unsigned int i;

	for (i = 0; datash->_environ[i]; i++)
	{
		free(datash->_environ[i]);
	}

	free(datash->_environ);
	free(datash->pid);
}

/**
 * set_datas -
 * @datash:
 * @av:
 * Return:
 */
void set_datas(data_shell *datash, char **av)
{
	unsigned int i;

	datash->av = av;
	datash->input = NULL;
	datash->args = NULL;
	datash->status = 0;
	datash->counter = 1;

	for (i = 0; environ[i]; i++)
		;

	datash->_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		datash->_environ[i] = _strdump(environ[i]);
	}

	datash->_environ[i] = NULL;
	datash->pid = aux_itoas(getpid());
}

/**
 * main -
 * @ac:
 * @av:
 * Return:
 */
int main(int ac, char **av)
{
	data_shell datash;
	(void)ac;

	signal(SIGINT, get_sigints);
	set_datas(&datash, av);
	shell_loops(&datash);
	free_datas(&datash);
	if (datash.status < 0)
		return (255);
	return (datash.status);
}
