#include "shell.h"

/**
 * cd_dots -
 * @datash:
 * Return:
 */
void cd_dots(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strlok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdump(pwd);
	set_env("OLDPWD", cp_pwd, datash);
	dir = datash->args[1];
	if (_strcomp(".", dir) == 0)
	{
		set_env("PWD", cp_pwd, datash);
		free(cp_pwd);
		return;
	}
	if (_strcomp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strlok_pwd = cp_pwd;
	rev_strings(cp_strlok_pwd);
	cp_strlok_pwd = _strlok(cp_strlok_pwd, "/");
	if (cp_strlok_pwd != NULL)
	{
		cp_strlok_pwd = _strlok(NULL, "\0");

		if (cp_strlok_pwd != NULL)
			rev_strings(cp_strlok_pwd);
	}
	if (cp_strlok_pwd != NULL)
	{
		chdir(cp_strlok_pwd);
		set_env("PWD", cp_strlok_pwd, datash);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", datash);
	}
	datash->status = 0;
	free(cp_pwd);
}

/**
 * cd_tos -
 *
 * @datash:
 * Return:
 */
void cd_tos(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = datash->args[1];
	if (chdir(dir) == -1)
	{
		get_errors(datash, 2);
		return;
	}

	cp_pwd = _strdump(pwd);
	set_env("OLDPWD", cp_pwd, datash);

	cp_dir = _strdump(dir);
	set_env("PWD", cp_dir, datash);

	free(cp_pwd);
	free(cp_dir);

	datash->status = 0;

	chdir(dir);
}

/**
 * cd_previouse -
 *
 * @datash:
 * Return:
 */
void cd_previouse(data_shell *datash)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdump(pwd);

	p_oldpwd = _getenv("OLDPWD", datash->_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdump(p_oldpwd);

	set_env("OLDPWD", cp_pwd, datash);

	if (chdir(cp_oldpwd) == -1)
		set_env("PWD", cp_pwd, datash);
	else
		set_env("PWD", cp_oldpwd, datash);

	p_pwd = _getenv("PWD", datash->_environ);

	write(STDOUT_FILENO, p_pwd, _strlenth(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	datash->status = 0;

	chdir(p_pwd);
}

/**
 * cd_tos_home -
 *
 * @datash:
 * Return:
 */
void cd_tos_home(data_shell *datash)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdump(pwd);

	home = _getenv("HOME", datash->_environ);

	if (home == NULL)
	{
		set_env("OLDPWD", p_pwd, datash);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_errors(datash, 2);
		free(p_pwd);
		return;
	}

	set_env("OLDPWD", p_pwd, datash);
	set_env("PWD", home, datash);
	free(p_pwd);
	datash->status = 0;
}
