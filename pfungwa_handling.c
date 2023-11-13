#include "shell.h"

/**
 * _memcpys -
 * @newptr:
 * @ptr:
 * @size:
 *
 * Return:
 */
void _memcpys(void *newptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_newptr = (char *)newptr;
	unsigned int i;

	for (i = 0; i < size; i++)
		char_newptr[i] = char_ptr[i];
}

/**
 * _reallocs -
 * @ptr:
 * @old_size:
 * @new_size:
 *
 * Return:
 */
void *_reallocs(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);

	if (new_size < old_size)
		_memcpys(newptr, ptr, new_size);
	else
		_memcpys(newptr, ptr, old_size);

	free(ptr);
	return (newptr);
}

/**
 * _reallocsdps -
 * @ptr:
 * @old_size:
 * @new_size:
 *
 * Return:
 */
char **_reallocsdps(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newptr;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(sizeof(char *) * new_size);
	if (newptr == NULL)
		return (NULL);

	for (i = 0; i < old_size; i++)
		newptr[i] = ptr[i];

	free(ptr);

	return (newptr);
}
