#include "shell.h"

/**
 * get_sigints -
 * @sig:
 */
void get_sigints(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n^-^ ", 5);
}
