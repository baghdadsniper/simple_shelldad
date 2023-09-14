#include "shell.h"

/**
 * clear_infos - initializes info_t strsuct
 * @info: strsuct address
 */
void clear_infos(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_infos - initializes info_t strsuct
 * @info: strsuct address
 * @av: argument vector
 */
void set_infos(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strstow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strsdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_alias(info);
		replace_varse(info);
	}
}

/**
 * free_infos - frees info_t strsuct fields
 * @info: strsuct address
 * @all: true if freeing all fields
 */
void free_infos(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_lists(&(info->env));
		if (info->history)
			free_lists(&(info->history));
		if (info->alias)
			free_lists(&(info->alias));
		ffree(info->environ);
		info->environ = NULL;
		bfrees((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
