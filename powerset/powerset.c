/*
* POWERSET
*
* allowed funcitons: atoi, fprintf, malloc, calloc, realloc, free, stdout, stderr, write
*
* This is an exercise in recursion. The goal is a program that takes as an argument strings
* containing first a number n in integer range, followed by a set s, all in integer range.
* The program should display all subsets of s, whose sum of elements is n.
* Order of printed subsets is unimportant, but order inside the subset should follow the order of s.
* There should be no duplicates in the output (3 4 1 and 1 3 4 are the same).
* In case of malloc error, the progrm should exit with exit code 1.
* No error checking for invalid sets is required.
* Example:
./powerset 3 1 0 2 4 9 5 3 | cat -e
1 0 2 $
1 2 $
0 3 $
3 $

./powerset 0 -2 2 | cat -e
$
-2 2 $

./powerset 3 2 1 4 0 | cat -e
2 1 $
2 1 0 $
* last example makes clear, that the algorithm shouldn't be optimized to stop, but keep searching for another option after the sum has been achieved.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	get_set(int *set, int size, char **from)
{
	int	i = -1;

	while (++i < size)
		set[i] = atoi(from[i]);
}

void	print_set(int *set, int size)
{
	int	i = -1;

	while (++i < size)
		fprintf(stdout, "%d ", set[i]);
	fprintf(stdout, "\n");
}

int	sum_set(int *set, int size)
{
	int	i = -1;
	int	sum = 0;

	while (++i < size)
		sum += set[i];
	return (sum);
}

void	pwrset(int *set, int size, int target, int *new, int i, int j, int sum)
{
	if (j == 0 && target == 0)
		fprintf(stdout, "\n");
	else if (sum_set(new, j) == target)
		print_set(new, j);
	while (i < size)
	{
		new[j] = set[i];
		pwrset(set, size, target, new, i + 1, j + 1, sum + set[j]);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	int	set[argc - 2];
	int target = atoi(argv[1]);
	int	new[argc - 2];

	get_set(set, argc - 2, argv + 2);
	pwrset(set, argc - 2, target, new, 0, 0, 0);
	return (0);
}
