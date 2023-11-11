#include "shell.h"

/**
 * cd_shell - 
 * @datash: 
 * Return: 
 */
int cd_shell(data_shell *datash)
{
	char *dir;
	int ishome, ishome2, isddash;

	dir = datash->args[1];

	if (dir != NULL)
	{
		ishome = _strcomp("$HOME", dir);
		ishome2 = _strcomp("~", dir);
		isddash = _strcomp("--", dir);
	}

	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		cd_to_home(datash);
		return (1);
	}

	if (_strcomp("-", dir) == 0)
	{
		cd_previous(datash);
		return (1);
	}

	if (_strcomp(".", dir) == 0 || _strcomp("..", dir) == 0)
	{
		cd_dot(datash);
		return (1);
	}

	cd_to(datash);

	return (1);
}
