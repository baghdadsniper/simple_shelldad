#include "shell.h"

/**
 * clear_info2 - initializes info_t struct
 * @info: struct address
 */
void clear_info2(info_t *info)
{
	info->arg2 = NULL;
	info->argv2 = NULL;
	info->path2 = NULL;
	info->argc2 = 0;
}

/**
 * set_info2 - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void set_info2(info_t *info, char **av)
{
	int i = 0;

	info->fname2 = av[0];
	if (info->arg2)
	{
		info->argv2 = strtow2(info->arg2, " \t");
		if (!info->argv2)
		{

			info->argv2 = malloc(sizeof(char *) * 2);
			if (info->argv2)
			{
				info->argv2[0] = _strdup2(info->arg2);
				info->argv2[1] = NULL;
			}
		}
		for (i = 0; info->argv2 && info->argv2[i]; i++)
			;
		info->argc2 = i;

		replace_alias2(info);
		replace_vars2(info);
	}
}

/**
 * free_info2 - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_info2(info_t *info, int all)
{
	ffree2(info->argv2);
	info->argv2 = NULL;
	info->path2 = NULL;
	if (all)
	{
		if (!info->cmd_buf2)
			free(info->arg2);
		if (info->env)
			free_list2(&(info->env));
		if (info->history2)
			free_list2(&(info->history2));
		if (info->alias2)
			free_list2(&(info->alias2));
		ffree2(info->environ2);
		info->environ2 = NULL;
		bfree2((void **)info->cmd_buf2);
		if (info->readfd2 > 2)
			close(info->readfd2);
		_putchar2(BUF_FLUSH);
	}
}
