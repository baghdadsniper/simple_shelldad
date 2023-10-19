#include "shell.h"

/**
 * is_cmd2 - determines if a file is an executable command
 * @info: the info struct
 * @path2: path2 to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd2(info_t *info, char *path2)
{
	struct stat st;

	(void)info;
	if (!path2 || stat(path2, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars2 - duplicates characters
 * @pathstr: the path2 string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars2(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path2 - finds this cmd in the path2 string
 * @info: the info struct
 * @pathstr: the path2 string
 * @cmd: the cmd to find
 *
 * Return: full path2 of cmd if found or NULL
 */
char *find_path2(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path2;

	if (!pathstr)
		return (NULL);
	if ((_strlen2(cmd) > 2) && starts_with2(cmd, "./"))
	{
		if (is_cmd2(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path2 = dup_chars2(pathstr, curr_pos, i);
			if (!*path2)
				_strcat2(path2, cmd);
			else
			{
				_strcat2(path2, "/");
				_strcat2(path2, cmd);
			}
			if (is_cmd2(info, path2))
				return (path2);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
