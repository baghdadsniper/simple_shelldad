#include "shell.h"

/**
 * aux_helps -
 * Return:
 */
void aux_helps(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, _strlenth(help));
	help = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, help, _strlenth(help));
	help = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, help, _strlenth(help));
}
/**
 * aux_helps_alias -
 * Return:
 */
void aux_helps_alias(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, _strlenth(help));
	help = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, help, _strlenth(help));
}
/**
 * aux_helps_cd -
 * Return:
 */
void aux_helps_cd(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, _strlenth(help));
	help = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, help, _strlenth(help));
}
