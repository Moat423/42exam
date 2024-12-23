#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>

/* 
* TRAVELING SALESMAN PROBLEM
*
* The traveling salesman problem (TSP) is a classic algorithmic problem in the fields of computer science and operations research.
* It needs a brute force approach to generate every possible round trip of a set of cities and select the shortest route.
*
* This particular implementation takes in city coordinates in the input stream (e.g. tsp <city-coords.txt)
* and retruns the shortest round trip distance on the command line.
*
* It uses a backtracking algorithm to generate every possible round trip and select the shortest one.
*/

//distance function to calculate the distance between two points
double distance(double x1, double y1, double x2, double y2) {
  return sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

// get the number of cities from the input stream
// uses getline to get number of lines and then sets read head back to start
int count_cities(void) {
  char *line = NULL;
  int bytes_read;
  int count = 0;
  size_t len = 0;

  while (true) {
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

// reads coordinates from input stream into cities array
void get_coordinates(double (*cities)[2], const int count) {
  int i = -1;

  while (++i < count)
    fscanf(stdin, "%lf, %lf", &cities[i][0], &cities[i][1]);
}

// my bzero, see man bzero
void ft_bzero(void *s, size_t n) {
  unsigned char *ptr = s;

  while (n--)
    *ptr++ = 0;
}

// checks array of visited to see if all cities have been visited
// retruns true if all cities have been visited
// returns false if not all cities have been visited
bool all_cities_visited(bool *visited, const int count) {
  int i = -1;

  while (++i < count)
    if (!visited[i])
      return (false);
  return (true);
}

// backtracking algorithm to generate every possible round trip and select the shortest one
void tsp(double (*cities)[2], const int count, bool *visited, int curr,
         double sum, double *result) {
  int next = -1;

	//base case
  if (all_cities_visited(visited, count)) {
    sum += distance(cities[curr][0], cities[curr][1], cities[0][0], cities[0][1]);
    if (sum < *result)
      *result = sum;
    return;
  }
	//assumptions generator
  while (++next < count) {
    if (visited[next])
      continue;
    visited[next] = true;
    double dist = distance(cities[curr][0], cities[curr][1], cities[next][0], cities[next][1]);
	if ((sum  + dist) < *result) // optimization (relevant good only more than 4 cities)
		tsp(cities, count, visited, next, sum + dist , result);
	visited[next] = false;
	//backtracking (going into next branch, with next assumption)
  }
}

int main(void) {
  int count = count_cities();
  bool visited[count];
  double cities[count][2];
  double result = DBL_MAX;

	clock_t start, end;
	double cpu_time_used;

	start = clock();

  if (count < 2)
    return 1;
  get_coordinates(cities, count);
  ft_bzero(visited, count * sizeof(bool));
  visited[0] = true;
  tsp(cities, count, visited, 0, 0.0, &result);
  fprintf(stdout, "%.2f\n", result);
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
printf("Execution time: %f seconds\n", cpu_time_used);


}
