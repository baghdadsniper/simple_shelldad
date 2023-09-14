#include "shell.h"

/**
 * **strstow - splits a strsing into words. Repeat delimiters are ignored
 * @strs: the input strsing
 * @d: the delimeter strsing
 * Return: a pointer to an array of strsings, or NULL on failure
hello
*/

char **strstow(char *strs, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (strs == NULL || strs[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; strs[i] != '\0'; i++)
		if (!is_delims(strs[i], d) && (is_delims(strs[i + 1], d) || !strs[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delims(strs[i], d))
			i++;
		k = 0;
		while (!is_delims(strs[i + k], d) && strs[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = strs[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strstow2 - splits a strsing into words
 * @strs: the input strsing
 * @d: the delimeter
 * Return: a pointer to an array of strsings, or NULL on failure
hello
*/
char **strstow2(char *strs, char d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (strs == NULL || strs[0] == 0)
		return (NULL);
	for (i = 0; strs[i] != '\0'; i++)
		if ((strs[i] != d && strs[i + 1] == d) ||
		    (strs[i] != d && !strs[i + 1]) || strs[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (strs[i] == d && strs[i] != d)
			i++;
		k = 0;
		while (strs[i + k] != d && strs[i + k] && strs[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = strs[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
