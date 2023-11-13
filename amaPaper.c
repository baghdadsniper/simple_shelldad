#include "shell.h"

/**
 * swap_chars -
 * @input:
 * @bool:
 * Return:
 */
char *swap_chars(char *input, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; input[i]; i++)
		{
			if (input[i] == '|')
			{
				if (input[i + 1] != '|')
					input[i] = 16;
				else
					i++;
			}

			if (input[i] == '&')
			{
				if (input[i + 1] != '&')
					input[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; input[i]; i++)
		{
			input[i] = (input[i] == 16 ? '|' : input[i]);
			input[i] = (input[i] == 12 ? '&' : input[i]);
		}
	}
	return (input);
}

/**
 * add_nodels -
 * @head_s:
 * @head_l:
 * @input:
 * Return:
 */
void add_nodels(sep_list **head_s, line_list **head_l, char *input)
{
	int i;
	char *line;

	input = swap_chars(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			add_sep_node_ends(head_s, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			add_sep_node_ends(head_s, input[i]);
			i++;
		}
	}

	line = _strlok(input, ";|&");
	do
	{
		line = swap_chars(line, 1);
		add_line_node_ends(head_l, line);
		line = _strlok(NULL, ";|&");
	} while (line != NULL);
}

/**
 * go_nexts -
 * @list_s:
 * @list_l:
 * @datash:
 * Return:
 */
void go_nexts(sep_list **list_s, line_list **list_l, data_shell *datash)
{
	int loop_sep;
	sep_list *ls_s;
	line_list *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (datash->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * split_commandos -
 * @datash:
 * @input:
 * Return:
 */
int split_commandos(data_shell *datash, char *input)
{
	sep_list *head_s, *list_s;
	line_list *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	add_nodels(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		datash->input = list_l->line;
		datash->args = split_lines(datash->input);
		loop = exec_lines(datash);
		free(datash->args);

		if (loop == 0)
			break;

		go_nexts(&list_s, &list_l, datash);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_sep_lists(&head_s);
	free_line_lists(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * split_lines -
 * @input:
 * Return:
 */
char **split_lines(char *input)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strlok(input, TOK_DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOK_BUFSIZE;
			tokens = _reallocsdps(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strlok(NULL, TOK_DELIM);
		tokens[i] = token;
	}

	return (tokens);
}
