#include "shell.h"

/**
 * get_history_file2 - gets the history2 file
 * @info: parameter struct
 *
 * Return: allocated string containg history2 file
 */

char *get_history_file2(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen2(dir) + _strlen2(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy2(buf, dir);
	_strcat2(buf, "/");
	_strcat2(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history2 - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history2(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file2(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history2; node; node = node->next)
	{
		_putsfd2(node->str, fd);
		_putfd2('\n', fd);
	}
	_putfd2(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history2 - reads history2 from file
 * @info: the parameter struct
 *
 * Return: histcount2 on success, 0 otherwise
 */
int read_history2(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file2(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list2(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list2(info, buf + last, linecount++);
	free(buf);
	info->histcount2 = linecount;
	while (info->histcount2-- >= HIST_MAX)
		delete_node_at_index2(&(info->history2), 0);
	renumber_history2(info);
	return (info->histcount2);
}

/**
 * build_history_list2 - adds entry to a history2 linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history2 linecount, histcount2
 *
 * Return: Always 0
 */
int build_history_list2(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history2)
		node = info->history2;
	add_node_end2(&node, buf, linecount);

	if (!info->history2)
		info->history2 = node;
	return (0);
}

/**
 * renumber_history2 - renumbers the history2 linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount2
 */
int renumber_history2(info_t *info)
{
	list_t *node = info->history2;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount2 = i);
}
