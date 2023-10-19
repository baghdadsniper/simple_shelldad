#include "shell.h"

/**
 * _myexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status2
 *         (0) if info.argv2[0] != "exit"
 */
int _myexit(info_t *info)
{
	int exitcheck2;

	if (info->argv2[1]) /* If there is an exit arguement */
	{
		exitcheck2 = _erratoi2(info->argv2[1]);
		if (exitcheck2 == -1)
		{
			info->status2 = 2;
			print_error2(info, "Illegal number: ");
			_eputs2(info->argv2[1]);
			_eputchar2('\n');
			return (1);
		}
		info->err_num2 = _erratoi2(info->argv2[1]);
		return (-2);
	}
	info->err_num2 = -1;
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
		_puts2("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv2[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret2 = /* TODO: what should this be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret2 = chdir(dir);
	}
	else if (_strcmp2(info->argv2[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts2(s);
			_putchar2('\n');
			return (1);
		}
		_puts2(_getenv(info, "OLDPWD=")), _putchar2('\n');
		chdir_ret2 = /* TODO: what should this be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret2 = chdir(info->argv2[1]);
	if (chdir_ret2 == -1)
	{
		print_error2(info, "can't cd to ");
		_eputs2(info->argv2[1]), _eputchar2('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
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

	arg_array = info->argv2;
	_puts2("help call works. Function not yet implemented \n");
	if (0)
		_puts2(*arg_array); /* temp att_unused workaround */
	return (0);
}
