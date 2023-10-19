#include "shell.h"

/**
 * hsh2 - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh2(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret2 = 0;

	while (r != -1 && builtin_ret2 != -2)
	{
		clear_info2(info);
		if (interactive2(info))
			_puts("$ ");
		_eputchar2(BUF_FLUSH);
		r = get_input2(info);
		if (r != -1)
		{
			set_info2(info, av);
			builtin_ret2 = find_builtin2(info);
			if (builtin_ret2 == -1)
				find_cmd2(info);
		}
		else if (interactive2(info))
			_putchar('\n');
		free_info2(info, 0);
	}
	write_history2(info);
	free_info2(info, 1);
	if (!interactive2(info) && info->status)
		exit(info->status);
	if (builtin_ret2 == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret2);
}

/**
 * find_builtin2 - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin2(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit2},
		{"env", _myenv2},
		{"help", _myhelp2},
		{"history", _myhistory2},
		{"setenv", _mysetenv2},
		{"unsetenv", _myunsetenv2},
		{"cd", _mycd2},
		{"alias", _myalias2},
		{NULL, NULL}};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd2 - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd2(info_t *info)
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
		if (!is_delim2(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path2(info, _getenv2(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd2(info);
	}
	else
	{
		if ((interactive2(info) || _getenv2(info, "PATH=") || info->argv[0][0] == '/') && is_cmd2(info, info->argv[0]))
			fork_cmd2(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error2(info, "not found\n");
		}
	}
}

/**
 * fork_cmd2 - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd2(info_t *info)
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
		if (execve(info->path, info->argv, get_environ2(info)) == -1)
		{
			free_info2(info, 1);
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
				print_error2(info, "Permission denied\n");
		}
	}
}
