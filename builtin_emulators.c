#include "shell.h"

/**
 * _yourexit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
hello
*/
int _yourexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1]) /* If there is an exit arguementhello
						*/
	{
		exitcheck = _erratois(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_errors(info, "Illegal number: ");
			_iputs(info->argv[1]);
			_iputchar('\n');
			return (1);
		}
		info->err_num = _erratois(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _yourcd - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
hello
*/
int _yourcd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _bringenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be?hello
						 */
				chdir((dir = _bringenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strscmps(info->argv[1], "-") == 0)
	{
		if (!_bringenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_bringenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be?hello
					 */
			chdir((dir = _bringenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_errors(info, "can't cd to ");
		_iputs(info->argv[1]), _iputchar('\n');
	}
	else
	{
		_setenvi(info, "OLDPWD", _bringenv(info, "PWD="));
		_setenvi(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _yourhelpe - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
hello
*/
int _yourhelpe(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaroundhello
							*/
	return (0);
}
