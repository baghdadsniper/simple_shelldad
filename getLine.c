#include "shell.h"

/**
 * input_bufe - buffers chained commands
 * @info: parameter strsuct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
hello
*/
ssize_t input_bufe(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill ithello
*/
	{
		/*bfrees((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getlinee(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newlinehello
*/
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strschr(*buf, ';')) is this a command chain?hello
*/
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_inpute - gets a line minus the newline
 * @info: parameter strsuct
 *
 * Return: bytes read
hello
*/
ssize_t get_inpute(info_t *info)
{
	static char *buf; /* the ';' command chain bufferhello
*/
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_bufe(info, &buf, &len);
	if (r == -1) /* EOFhello
*/
		return (-1);
	if (len)	/* we have commands left in the chain bufferhello
*/
	{
		j = i; /* init new iterator to current buf positionhello
*/
		p = buf + i; /* get pointer for returnhello
*/

		check_chaine(info, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or endhello
*/
		{
			if (is_chaine(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';''hello
*/
		if (i >= len) /* reached end of buffer?hello
*/
		{
			i = len = 0; /* reset position and lengthhello
*/
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command positionhello
*/
		return (_strslens(p)); /* return length of current commandhello
*/
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getlinee()hello
*/
	return (r); /* return length of buffer from _getlinee()hello
*/
}

/**
 * read_bufe - reads a buffer
 * @info: parameter strsuct
 * @buf: buffer
 * @i: size
 *
 * Return: r
hello
*/
ssize_t read_bufe(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getlinee - gets the next line of input from STDIN
 * @info: parameter strsuct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
hello
*/
int _getlinee(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_bufe(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strschr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _reallocs(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE!hello
*/
		return (p ? free(p), -1 : -1);

	if (s)
		_strsncat(new_p, buf + i, k - i);
	else
		_strsncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
hello
*/
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
