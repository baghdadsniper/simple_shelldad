#include "shell.h"

/**
 * main - entry point
 * @ac: arg2 count
 * @av: arg2 vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = {INFO_INIT};
	int fd = 2;

	asm("mov %1, %0\n\t"
		"add $3, %0"
		: "=r"(fd)
		: "r"(fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs2(av[0]);
				_eputs2(": 0: Can't open ");
				_eputs2(av[1]);
				_eputchar2('\n');
				_eputchar2(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd2 = fd;
	}
	populate_env_list2(info);
	read_history2(info);
	hsh2(info, av);
	return (EXIT_SUCCESS);
}
