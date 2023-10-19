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
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info2(info);
		if (interactive4(info))
			_puts432("$ ");
		_eputchar2(BUF_FLUSH);
		r = get_input2(info);
		if (r != -1)
		{
			set_info23(info, av);
			builtin_ret = find_builtin2(info);
			if (builtin_ret == -1)
				find_cmd2(info);
		}
		else if (interactive4(info))
			_putchar4('\n');
		free_info22(info, 0);
	}
	write_history(info);
	free_info22(info, 1);
	if (!interactive4(info) && info->status)
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
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp2(info->argv[0], builtintbl[i].type) == 0)
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
		if (!is_delim54(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path23(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd2(info);
	}
	else
	{
		if ((interactive4(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd3(info, info->argv[0]))
			fork_cmd2(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error3(info, "not found\n");
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
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info22(info, 1);
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
				print_error3(info, "Permission denied\n");
		}
	}
}
