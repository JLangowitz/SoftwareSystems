#include <stdio.h>
#include <stdlib.h>

#include "rand.c"

int main (int argc, char *argv[])
{
  int i;
  int tests = 10000000;
  double x;
  int n = tests/10000;
  int buckets[n];
  for (i=0; i<n; i++) {
    buckets[i] = 0;
  } 
  int j;
  int abs_error = 0;
  int error;

  srandom (time (NULL));

  for (i=0; i<tests; i++) {
    x = my_random_double();
    for (j=0; j<n; j++) {
      if (x < (float)(j+1)/n){
        buckets[j]++;
        break;
      }
    }
  }
  for (i=0; i<n; i++) {
    error = buckets[i] - tests/n;
    if (error < 0)
        error = -error;
    abs_error+=error;
  } 
  printf("%i\n", abs_error);
  return 0;
}
