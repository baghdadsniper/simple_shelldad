#include "shell.h"

int _myexit(info_t *info)
{
    int exit_status = 0;

    if (info->argv[1])
    {
        exit_status = atoi(info->argv[1]);
        if (exit_status == 0 && info->argv[1][0] != '0')
        {
            info->status = 2;
            print_error(info, "Illegal number: ");
            _eputs(info->argv[1]);
            _eputchar('\n');
            return 1;
        }
        info->err_num = exit_status;
        return -2;
    }

    info->err_num = -1;
    return -2;
}

int _mycd(info_t *info)
{
    char *dir;
    char buffer[1024];

    if (!info->argv[1])
    {
        dir = _getenv(info, "HOME=");
        if (!dir)
            dir = _getenv(info, "PWD=");
    }
    else if (_strcmp(info->argv[1], "-") == 0)
    {
        dir = _getenv(info, "OLDPWD=");
        if (!dir)
        {
            _puts("TODO: >>getenv failure emsg here<<\n");
            return 1;
        }
        _puts(dir);
        _putchar('\n');
    }
    else
    {
        dir = info->argv[1];
    }

    if (chdir(dir) == -1)
    {
        print_error(info, "can't cd to ");
        _eputs(info->argv[1]);
        _eputchar('\n');
    }
    else
    {
        _setenv(info, "OLDPWD", _getenv(info, "PWD="));
        _setenv(info, "PWD", getcwd(buffer, 1024));
    }

    return 0;
}

int _myhelp(info_t *info)
{
    char **arg_array = info->argv;

    _puts("help call works. Function not yet implemented \n");
    if (0)
        _puts(*arg_array); /* temp att_unused workaround */

    return 0;
}