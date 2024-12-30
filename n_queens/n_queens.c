/*
* N-Queens Problem
*
* This is a solution to the N-Queens problem using a recursive backtracking algorithm 
* for a given board size 'n'.
* It prints all possible solutions where 'n' queens can be placed on an n x n chessboard
* without threatening each other. Solutions are displayed as sequences of column positions.
* 
* Example:
* ./n_queens 4
* 1 3 0 2
* 2 0 3 1
*/

#include <stdio.h>
#include <stdlib.h>

// set a sequence to whatever n is
void	ft_bn(void *s, size_t i, int n)
{
	unsigned char *p = s;

	while (i--)
		*p++ = n;
}

// check if queen can be placed in a given position
int	is_safe(int board_size, int *solutions, int col)
{
	int	 i = -1;

	while (++i < col)
	{
		if (solutions[col] == solutions[i])
			return (0);
		if (solutions[col] == solutions[i] - i + col)
			return (0);
		if (solutions[col] == solutions[i] + i - col)
			return (0);
	}
	return (1);
}

// print state of board (columns seperated by spaces, position of queen as number from 0 to n-1)
void	print_board(int solutions[], int board_size)
{
	int	i = -1;

	(void) board_size;
	while (++i < board_size)
		printf("%d ", solutions[i]);
	printf("\n");
}

// backtrack to find solution
void	calc_board(int board_size, int col, int *solutions)
{
	int i = -1;

	if (col == board_size)
	{
		print_board(solutions, board_size);
		return ;
	}
	while (++i < board_size)
	{
		solutions[col] = i;
		if (is_safe(board_size, solutions, col))
			calc_board(board_size, col + 1, solutions);
		solutions[col] = -1;
	}
}

int	main(int argc, char *argv[])
{
	int	board_size;
	if (argc != 2)
		return (1);
	board_size = atoi(argv[1]);
	if (board_size < 1)
		return (1);
	int solutions[board_size];
	ft_bn(solutions, board_size, -1); // set board to -1 in all slots
	calc_board(board_size, 0, solutions);
	return (0);
}
