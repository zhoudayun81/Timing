/*Timing2.c*/

#include <stdio.h>
#include <time.h>
#include <assert.h>

int modExp(int y, long int k, int n); 

void timespec_diff(struct timespec *start, struct timespec *stop,
                   struct timespec *result)
{
    if ((stop->tv_nsec - start->tv_nsec) < 0) {
        result->tv_sec = stop->tv_sec - start->tv_sec - 1;
        result->tv_nsec = stop->tv_nsec - start->tv_nsec + 1000000000;
    } else {
        result->tv_sec = stop->tv_sec - start->tv_sec;
        result->tv_nsec = stop->tv_nsec - start->tv_nsec;
    }

    return;
}

int main()
{
  int y, n;
  long int k, result, loop; /* useless but necessary y */

  struct timespec interval, start, end;

  FILE *input;

  /*read generated input feed file, and write the time ticks to the output file*/
  input = fopen("input", "r");
  while(fscanf(input, "%d %d %ld %ld", &y, &n, &loop, &k)!=EOF)
  {
    for (int i = 0; i < loop; i++)
    {
      clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
      result = modExp(y, k, n);
      clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
      timespec_diff(&start, &end, &interval);
      assert(interval.tv_sec == 0);
      printf("%ld  %ld\n", k, interval.tv_nsec);
    }
  }
  fclose(input);
  printf("Finished!\n");
  return 0;
}

int modExp(int y, long int k, int n)
{
  int r = 1;
  int i;
  for (i = 0; i < 32; i++)
  {
    if (k % 2 == 1)
      r = (r*y) % n;
    y = (y*y) % n;
    k >>= 1;
  }
  return r%n;
}
