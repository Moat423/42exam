#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <float.h>
//
//alternative tsp function for tsp.c

void tsp(double (*cities)[2], bool *visited, int count, int current, int
depth,
         double sum, double *result) {
  double dist;
  int i;

  if (all_cities_visited(visited, count) || depth == count) {
    dist = distance(cities[current][0], cities[current][1], cities[0][0],
                    cities[0][1]);
    sum += dist;
    if (sum < *result)
      *result = sum;
    return;
  }

  for (i = 0; i < count; i++) {
    if (!visited[i]) {
      dist = distance(cities[current][0], cities[current][1], cities[i][0],
                      cities[i][1]);
      visited[i] = true;
      tsp(cities, visited, count, i, depth + 1, sum + dist, result);
      visited[i] = false;
    }
  }
  return;
}

int main(void) {
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
  tsp(cities, visited, count, 0, 1, sum, &result);
  fprintf(stdout, "%.2f\n", result);
}
