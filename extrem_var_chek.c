#include "shell.h"

/**
 * check_envs -
 * @h:
 * @in:
 * @data:
 * Return:
 */
void check_envs(r_var **h, char *in, data_shell *data)
{
	int row, chr, j, lval;
	char **_envr;

	_envr = data->_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (j = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = _strlenth(_envr[row] + chr + 1);
				add_var_node(h, j, _envr[row] + chr + 1, lval);
				return;
			}

			if (in[j] == _envr[row][chr])
				j++;
			else
				break;
		}
	}

	for (j = 0; in[j]; j++)
	{
		if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
			break;
	}

	add_var_node(h, j, NULL, 0);
}

/**
 * check_var -
 * @h:
 * @in:
 * @st:
 * @data:
 * Return:
 */
int check_var(r_var **h, char *in, char *st, data_shell *data)
{
	int i, lst, lpd;

	lst = _strlenth(st);
	lpd = _strlenth(data->pid);

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				add_var_node(h, 2, st, lst), i++;
			else if (in[i + 1] == '$')
				add_var_node(h, 2, data->pid, lpd), i++;
			else if (in[i + 1] == '\n')
				add_var_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				add_var_node(h, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				add_var_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				add_var_node(h, 0, NULL, 0);
			else if (in[i + 1] == ';')
				add_var_node(h, 0, NULL, 0);
			else
				check_envs(h, in + i, data);
		}
	}

	return (i);
}

/**
 * replace_input -
 *
 * @head:
 * @input:
 * @new_input:
 * @nlen:
 * Return:
 */
char *replace_input(r_var **head, char *input, char *new_input, int nlen)
{
	r_var *indx;
	int i, j, k;

	indx = *head;
	for (j = i = 0; i < nlen; i++)
	{
		if (input[j] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_input[i] = input[j];
				j++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (k = 0; k < indx->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < indx->len_val; k++)
				{
					new_input[i] = indx->val[k];
					i++;
				}
				j += (indx->len_var);
				i--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[i] = input[j];
			j++;
		}
	}

	return (new_input);
}

/**
 * rep_vars -
 *
 * @input:
 * @datash:
 * Return:
 */
char *rep_vars(char *input, data_shell *datash)
{
	r_var *head, *indx;
	char *status, *new_input;
	int olen, nlen;

	status = aux_itoas(datash->status);
	head = NULL;

	olen = check_var(&head, input, status, datash);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = replace_input(&head, input, new_input, nlen);

	free(input);
	free(status);
	free_var_list(&head);

	return (new_input);
}
