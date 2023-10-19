#include "shell.h"

/**
 * input_buf2 - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf2(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree2((void **)info->cmd_buf2);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler2);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline2(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->linecount_flag2 = 1;
			remove_comments2(*buf);
			build_history_list2(info, *buf, info->histcount2++);
			/* if (_strchr2(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->cmd_buf2 = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input2 - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input2(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg2), *p;

	_putchar2(BUF_FLUSH);
	r = input_buf2(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		j = i;		 /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */

		check_chain2(info, buf, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_chain2(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;	  /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			info->cmd_buf_type2 = CMD_NORM;
		}

		*buf_p = p;			  /* pass back pointer to current command position */
		return (_strlen2(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline2() */
	return (r);	  /* return length of buffer from _getline2() */
}

/**
 * read_buf2 - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf2(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd2, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline2 - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline2(info_t *info, char **ptr, size_t *length)
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

	r = read_buf2(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr2(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc2(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat2(new_p, buf + i, k - i);
	else
		_strncpy2(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler2 - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler2(__attribute__((unused)) int sig_num)
{
	_puts2("\n");
	_puts2("$ ");
	_putchar2(BUF_FLUSH);
}
