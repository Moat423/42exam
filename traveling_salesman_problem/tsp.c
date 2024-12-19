#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <float.h>


float	distance(double x1, double y1, double x2, double y2)
{
	double x = x2 - x1;
	double y = y2 - y1;
	return (sqrt(x * x + y * y));
}

int	count_cities(void)
{
	char *line = NULL;
	int	bytes_read;
	int	count = 0;
	size_t	len = 0;

	while (true)
	{
		bytes_read = getline(&line, &len, stdin);
		free(line);
		line = NULL;
		if (bytes_read == -1)
			break;
		count++;
	}
	fseek(stdin, 0, SEEK_SET);
	return (count);
}

void	get_coordinates(double (*cities)[2], const int count)
{
	int	i = -1;

	while (++i < count)
		scanf("%lf %lf", &cities[i][0], &cities[i][1]);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr = s;

	while (n--)
		*ptr++ = 0;
}

bool	all_cities_visited(bool *visited, const int count)
{
	int	i = -1;

	while (++i < count)
		if (!visited[i])
			return (false);
	return (true);
}

// void	tsp(double (*cities)[2], const int count, bool *visited, int curr, double sum, double *result)
// {
// 	int		next = -1;
//
// 	if (all_cities_visited(visited, count))
// 	{
// 		sum += distance(cities[curr][0], cities[curr][1], cities[0][0], cities[0][1]);
// 		if (sum < *result)
// 			*result = sum;
// 		return ;
// 	}
// 	while (++next < count)
// 	{
// 		if (visited[next])
// 			continue;
// 		visited[next] = true;
// 		double dist = distance(cities[curr][0], cities[curr][1], cities[next][0], cities[next][1]);
// 		tsp(cities, count, visited, next, sum + dist, result);
// 		visited[next] = false;
// 	}
// }

double tsp(double (*cities)[2], bool *visited, int count, int current, int depth, double sum, double result)
{
    double dist;
    int i;

    if (depth == count)
    {
        sum += distance(cities[current][0], cities[current][1], cities[0][0], cities[0][1]);
        if (sum < result)
            result = sum;
        return result;
    }

    visited[current] = true;
    for (i = 0; i < count; i++)
    {
        if (!visited[i])
        {
            dist = distance(cities[current][0], cities[current][1], cities[i][0], cities[i][1]);
            result = tsp(cities, visited, count, i, depth + 1, sum + dist, result);
        }
    }
    visited[current] = false;
    return result;
}

int	main(void)
{
	int count = count_cities();
	bool visited[count];
	double cities[count][2];
	double result = DBL_MAX;
	double sum = 0.0;

	if (count < 2)
		return 1;
	get_coordinates(cities, count);
	ft_bzero(visited, count * sizeof(bool));
	visited[0] = true;
	// tsp(cities, count, visited, 0, 0.0, &result);
	result = tsp(cities, visited, count, 0, 1, sum, result);
	fprintf(stdout, "%.2f\n", result);
}
