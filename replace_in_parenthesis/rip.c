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
*/

#include <unistd.h>
#include <stdio.h>


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

void	rip(char *str, int balanced, char *curr)
{
	int	converted = 0;
	//base case
	if (is_balanced(str))
	{
		write(1, &curr, ft_strlen(curr));
		return ;
	}
	//assumptions generator depth first
	while (*curr)
	{
		if (*curr == '(')
			open++;
		else
			open--;
		if ((balanced > 0 && *curr == '(') || (balanced < 0 && *curr == ')'))
		{
			converted++;
			*curr = ' ';
		}
		rip(str, balanced, curr + 1);
		if (balanced < 0)
			*curr = ')';
		else if (balanced > 0)
			*curr = '(';
	}
	return ;
}

int	main(int argc, char *argv[])
{
	int	balanced;
	int	i = 0;

	if (argc != 2 || !argv[1])
		return (1);
	balanced = is_balanced(argv[1]);
	if (!balanced)
		puts(argv[1]);
	printf("balanced: %d\n", balanced);
}
