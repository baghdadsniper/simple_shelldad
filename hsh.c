#include "shell.h"

/**
 * hshs - main shell loop
 * @info: the parameter & return info strsuct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hshs(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_infos(info);
		if (interactives(info))
			_puts("$ ");
		_iputchar(BUF_FLUSH);
		r = get_inpute(info);
		if (r != -1)
		{
			set_infos(info, av);
			builtin_ret = find_builtins(info);
			if (builtin_ret == -1)
				find_cmds(info);
		}
		else if (interactives(info))
			_putchar('\n');
		free_infos(info, 0);
	}
	write_history(info);
	free_infos(info, 1);
	if (!interactives(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtins - finds a builtin command
 * @info: the parameter & return info strsuct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtins(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _yourquit},
		{"env", _yourenv},
		{"help", _yourhelpe},
		{"history", _yourhistorye},
		{"setenv", _yoursetenv},
		{"unsetenv", _yourunsetenv},
		{"cd", _yourcd},
		{"alias", _youralias},
		{NULL, NULL}};

	for (i = 0; builtintbl[i].type; i++)
		if (_strscmps(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmds - finds a command in PATH
 * @info: the parameter & return info strsuct
 *
 * Return: void
 */
void find_cmds(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delims(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_paths(info, _bringenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmds(info);
	}
	else
	{
		if ((interactives(info) || _bringenv(info, "PATH=") || info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmds(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_errors(info, "not found\n");
		}
	}
}

/**
 * fork_cmds - forks a an exec thread to run cmd
 * @info: the parameter & return info strsuct
 *
 * Return: void
 */
void fork_cmds(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environm(info)) == -1)
		{
			free_infos(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_errors(info, "Permission denied\n");
		}
	}
}
