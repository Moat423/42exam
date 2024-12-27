/*
* BALANCE PARENTHESIS
*
* This is an exercise for practising understanding and use of backtracking algorithms
* using only the most basic and simple c library functions. (puts and write)
*
* This particular exercise takes as an argument a single string consisting only of parentheseis
* If the string contains the same ammount of opening and closing brackets and is "balanced",
* it is echoed to stdout.
* Otherwise it prints all possible variations of replacing brackets to make the string balanced
* seperated by newlines.
* Order of different variations is not important.
* example:
*                 "())"  (i = 0)
                   |
                 "())"  (i = 1)
               /     \
           "())"     "( )"  (i = 2)
          /    \       |
     "())"   "() "    [B]  (i = 3)
	  |        |
     [X]      [B]

output:
() 
( )
[B] = Balanced, print
[X] = Not balanced, don't print
*/

#include <unistd.h>
#include <stdio.h>

#define abs(x) ((x) < 0 ? -(x) : (x))

// see man strlen
int	ft_strlen(const char *str)
{
	int	len = 0;

	while (str[len])
		len++;
	return (len);
}

// returns the number of parenthenthesis that is too much.
// returns a positive number if too many opening brackets (
// returns (as a negative) the number of closing brackets that are more than the number of opening brackets 
// if equal ammounts of opening and closing brackets, returns 0.
int	is_balanced(const char *str)
{
	int	count = 0;
	int	i = -1;
	int	len = ft_strlen(str);

	while (++i < len)
	{
		if (str[i] == '(')
			count++;
		else if (str[i] == ')')
			count--;
	}
	return (count);
}

int	count_brackets(const char *str, int *open, int *close)
{
	while (*str)
	{
		if (*str == '(')
			(*open)++;
		else if (*str == ')')
			(*close)++;
		else
			return (0);
		str++;
	}
	return (1);
}

void	rip(char *str, int i, int open, int closed, int to_remove)
{
	//end
	if (!to_remove)
	{
		if (is_balanced(str) == 0)
			puts(str);
		return ;
	}
	if (!str[i])
		return ;
	//assumptions generator depth first
	if (open > closed && str[i] == '(')
	{
		str[i] = ' ';
		rip(str, i + 1, open - 1, closed, to_remove - 1);
		str[i] = '(';
		rip(str, i + 1, open, closed, to_remove);
	}
	else if (open < closed && str[i] == ')')
	{
		str[i] = ' ';
		rip(str, i + 1, open, closed - 1, to_remove - 1);
		str[i] = ')';
		rip(str, i + 1, open, closed, to_remove);
	}
	else
		rip(str, i + 1, open, closed, to_remove);
}

int	main(int argc, char *argv[])
{
	int	open = 0;
	int	closed = 0;
	int	to_remove = 0;

	if (argc != 2 || !argv[1])
		return (1);
	if (!count_brackets(argv[1], &open, &closed))
		return (1);
	to_remove = abs(open - closed);
	if (!to_remove)
		puts(argv[1]);
	rip(argv[1], 0, open, closed, to_remove);
}
