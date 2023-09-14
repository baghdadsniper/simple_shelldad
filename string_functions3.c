#include "shell.h"

/**
 **_strsncpy - copies a strsing
 *@dest: the destination strsing to be copied to
 *@src: the source strsing
 *@n: the amount of characters to be copied
 *Return: the concatenated strsing
 */
char *_strsncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strsncat - concatenates two strsings
 *@dest: the first strsing
 *@src: the second strsing
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated strsing
 */
char *_strsncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 **_strschr - locates a character in a strsing
 *@s: the strsing to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strschr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
