#include "sandbox.h"

void	ft_segfault(void)
{
	printf("segfault:\n");
	char	*str = NULL;
	str[0] = 0;
}

void	ft_forever(void)
{
	printf("running forever\n");
	while (1){};
}

void	ft_nice(void)
{
	printf("nice function\n");
}

void	ft_abort(void)
{
	printf("abort\n");
	abort();
}

void	ft_exit(void)
{
	printf("exit 0\n");
	exit(0);
}

void	ft_exit1(void)
{
	printf("exit 1\n");
	exit(1);
}

int	main(void)
{
	sandbox(ft_forever, 2, true);
	sandbox(ft_segfault, 2, true);
	sandbox(ft_abort, 2, true);
	sandbox(ft_nice, 2, true);
	sandbox(ft_exit, 2, true);
	sandbox(ft_exit1, 2, true);
	return (0);
}
