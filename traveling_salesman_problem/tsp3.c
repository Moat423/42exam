#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <float.h>

#define CITY_0 0
#define NO_PREV -1

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
void tsp(double c[][2], bool *visited, double current_dist, double *min_dist, int count, int prev)
{
    // Base case: all cities visited
    if (all_cities_visited(visited, count))
    {
        // Add distance back to the starting city
        if (prev != NO_PREV)
        {
            current_dist += distance(c[prev][0], c[prev][1], c[CITY_0][0], c[CITY_0][1]);
        }
        if (current_dist < *min_dist)
        {
            *min_dist = current_dist;
        }
        return;
    }

    // First call: start with CITY_0
    if (prev == NO_PREV)
    {
        visited[CITY_0] = true;
        tsp(c, visited, 0.0, min_dist, count, CITY_0);
        return;
    }

    // Explore all unvisited cities
    for (int next = 0; next < count; next++)
    {
        if (!visited[next])
        {
            visited[next] = true;
            double dist = distance(c[prev][0], c[prev][1], c[next][0], c[next][1]);
            tsp(c, visited, current_dist + dist, min_dist, count, next);
            visited[next] = false; // backtrack
        }
    }
}

int main(void)
{
    int count = count_cities();
    double c[count][2];
    bool visited[count];
    double min_dist = DBL_MAX;

    get_coordinates(c, count);
    for (int i = 0; i < count; i++)
        visited[i] = false;
    tsp(c, visited, 0.0, &min_dist, count, NO_PREV);
    printf("%.2f\n", min_dist);

    return 0;
}
