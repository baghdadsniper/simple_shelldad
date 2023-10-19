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
			_puts2("$ ");
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
			_putchar2('\n');
		free_info2(info, 0);
	}
	write_history2(info);
	free_info2(info, 1);
	if (!interactive2(info) && info->status2)
		exit(info->status2);
	if (builtin_ret2 == -2)
	{
		if (info->err_num2 == -1)
			exit(info->status2);
		exit(info->err_num2);
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
		{"exit", _myexit},
		{"env2", _myenv2},
		{"help", _myhelp2},
		{"history2", _myhistory2},
		{"setenv", _mysetenv2},
		{"unsetenv", _myunsetenv2},
		{"cd", _mycd2},
		{"alias2", _myalias2},
		{NULL, NULL}};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp2(info->argv2[0], builtintbl[i].type) == 0)
		{
			info->line_count2++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd2 - finds a command in path2
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd2(info_t *info)
{
	char *path2 = NULL;
	int i, k;

	info->path2 = info->argv2[0];
	if (info->linecount_flag2 == 1)
	{
		info->line_count2++;
		info->linecount_flag2 = 0;
	}
	for (i = 0, k = 0; info->arg2[i]; i++)
		if (!is_delim2(info->arg2[i], " \t\n"))
			k++;
	if (!k)
		return;

	path2 = find_path2(info, _getenv2(info, "path2="), info->argv2[0]);
	if (path2)
	{
		info->path2 = path2;
		fork_cmd2(info);
	}
	else
	{
		if ((interactive2(info) || _getenv2(info, "path2=") || info->argv2[0][0] == '/') && is_cmd2(info, info->argv2[0]))
			fork_cmd2(info);
		else if (*(info->arg2) != '\n')
		{
			info->status2 = 127;
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
		if (execve(info->path2, info->argv2, get_environ2(info)) == -1)
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
		wait(&(info->status2));
		if (WIFEXITED(info->status2))
		{
			info->status2 = WEXITSTATUS(info->status2);
			if (info->status2 == 126)
				print_error2(info, "Permission denied\n");
		}
	}
}
