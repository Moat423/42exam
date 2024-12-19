
double	tsp(double (*cities)[2], const int count, bool *visited, int current, int depth, double result)
{
	double dist;
	double temp;
	int i;
	if (depth == count)
	{
		dist = distance(cities[current][0], cities[current][1], cities[0][0], cities[0][1]);
		if (dist < result)
			result = dist;
		return (result);
	}
	visited[current] = true;
	for (i = 0; i < count; i++)
	{
		if (!visited[i])
		{
			temp = distance(cities[current][0], cities[current][1], cities[i][0], cities[i][1]);
			if (temp < result)
				result = tsp(cities, visited, count, i, depth + 1, result);
		}
	}
	visited[current] = false;
	return (result);
}
