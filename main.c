#include "shell.h"

/**
 * main - entry point to the program
 * @ac: argument count integer variable
 * @av: argument list pointer to char variable
 *
 * Return: 0 on success or 1 on error
 */
int main(int ac, char **av)
{
	info_t infomation_list[] = { INFO_INIT };
	int filed = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (filed)
			: "r" (filed));

	if (ac == 2)
	{
		filed = open(av[1], O_RDONLY);
		if (filed == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		infomation_list->readfd = filed;
	}
	populate_env_list(infomation_list);
	read_history(infomation_list);
	hsh(infomation_list, av);
	return (EXIT_SUCCESS);
}