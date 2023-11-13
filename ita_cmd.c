#include "shell.h"

/**
 * is_cdirs -
 * @path:
 * @i:
 * Return:
 */
int is_cdirs(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * _whichs -
 * @cmd:
 * @_environ:
 * Return:
 */
char *_whichs(char *cmd, char **_environ)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = _getenv("PATH", _environ);
	if (path)
	{
		ptr_path = _strdump(path);
		len_cmd = _strlenth(cmd);
		token_path = _strlok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (is_cdirs(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = _strlenth(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			_strcopy(dir, token_path);
			_strdog(dir, "/");
			_strdog(dir, cmd);
			_strdog(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = _strlok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * is_executables -
 * @datash:
 * Return:
 */
int is_executables(data_shell *datash)
{
	struct stat st;
	int i;
	char *input;

	input = datash->args[0];
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(input + i, &st) == 0)
	{
		return (i);
	}
	get_errors(datash, 127);
	return (-1);
}

/**
 * check_error_cmds -
 * @dir:
 * @datash:
 * Return:
 */
int check_error_cmds(char *dir, data_shell *datash)
{
	if (dir == NULL)
	{
		get_errors(datash, 127);
		return (1);
	}

	if (_strcomp(datash->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_errors(datash, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(datash->args[0], X_OK) == -1)
		{
			get_errors(datash, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * cmd_execs -
 * @datash:
 * Return:
 */
int cmd_execs(data_shell *datash)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void)wpd;

	exec = is_executables(datash);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = _whichs(datash->args[0], datash->_environ);
		if (check_error_cmds(dir, datash) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = _whichs(datash->args[0], datash->_environ);
		else
			dir = datash->args[0];
		execve(dir + exec, datash->args, datash->_environ);
	}
	else if (pd < 0)
	{
		perror(datash->av[0]);
		return (1);
	}
	else
	{
		do
		{
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	datash->status = state / 256;
	return (1);
}
