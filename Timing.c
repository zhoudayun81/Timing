#include <stdio.h>
#include <time.h>
#include <stdint.h>

int modExp(int y, long int k, int n); 
void timespec_diff(struct timespec *start, struct timespec *stop, struct timespec *result);

int main()
{
  int y, n;
  uint32_t k, result, loop; /* useless but necessary y */

  struct timespec interval, start, end;

  FILE *input;
  input = fopen("input", "r");

  int index = 0;

  while(fscanf(input, "%d %d %u %u", &y, &n, &loop, &k)!=EOF)
  {
    for (int i = 0; i < loop; i++)
    {
      clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
      result = modExp(y, k, n);
      clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
      timespec_diff(&start, &end, &interval);
      printf("%d %ld\n", index, interval.tv_nsec);
    }
    index++;
  }
  fclose(input);
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

void timespec_diff(struct timespec *start, struct timespec *stop, struct timespec *result)
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

