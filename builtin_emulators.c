#include "shell.h"

/**
 * _myexit2 - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _myexit2(info_t *info)
{
	int exitcheck2;

	if (info->argv[1]) /* If there is an exit arguement */
	{
		exitcheck2 = _erratoi2(info->argv[1]);
		if (exitcheck2 == -1)
		{
			info->status = 2;
			print_error2(info, "Illegal number: ");
			_eputs2(info->argv[1]);
			_eputchar2('\n');
			return (1);
		}
		info->err_num = _erratoi2(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd2 - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _mycd2(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret2;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv2(info, "HOME=");
		if (!dir)
			chdir_ret2 = /* TODO: what should this be? */
				chdir((dir = _getenv2(info, "PWD=")) ? dir : "/");
		else
			chdir_ret2 = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv2(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv2(info, "OLDPWD=")), _putchar('\n');
		chdir_ret2 = /* TODO: what should this be? */
			chdir((dir = _getenv2(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret2 = chdir(info->argv[1]);
	if (chdir_ret2 == -1)
	{
		print_error2(info, "can't cd to ");
		_eputs2(info->argv[1]), _eputchar2('\n');
	}
	else
	{
		_setenv2(info, "OLDPWD", _getenv2(info, "PWD="));
		_setenv2(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp2 - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myhelp2(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
