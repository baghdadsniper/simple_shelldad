#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: the info strsuct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
hello
*/
int is_cmd(info_t *info, char *path)
{
	strsuct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_charss - duplicates characters
 * @pathstrs: the PATH strsing
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
hello
*/
char *dup_charss(char *pathstrs, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstrs[i] != ':')
			buf[k++] = pathstrs[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_paths - finds this cmd in the PATH strsing
 * @info: the info strsuct
 * @pathstrs: the PATH strsing
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
hello
*/
char *find_paths(info_t *info, char *pathstrs, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstrs)
		return (NULL);
	if ((_strslens(cmd) > 2) && starts_withs(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstrs[i] || pathstrs[i] == ':')
		{
			path = dup_charss(pathstrs, curr_pos, i);
			if (!*path)
				_strscat(path, cmd);
			else
			{
				_strscat(path, "/");
				_strscat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstrs[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
