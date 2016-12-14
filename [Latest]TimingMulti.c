#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

int modExp(int y, int k, int n); 
void timespec_diff(struct timespec *start, struct timespec *stop, struct timespec *result);

int main(int argc, char *argv[])
{
	if(argc!=2)
	{
		fprintf(stderr, "Usage: <integer from 1-5>  1.CLOCK_THREAD_CPUTIME_ID 2.CLOCK_PROCESS_CPUTIME_ID 3.CLOCK_MONOTONIC_RAW 4.CLOCK_MONOTONIC 5.CLOCK_REALTIME\n");
	}
	int y, n, k, loop, result;/* useless but necessary y */
	int clock_specifier = 1;
	
	if(argc == 2)
		clock_specifier = atoi(argv[1]);
		
	struct timespec interval, start, end;
	/*read generated input feed file, and write the time ticks to the output file*/
	FILE *input;
	input = fopen("input", "r");
	switch(clock_specifier) 
	{
		case 1 :
			while(fscanf(input, "%d %d %d %d", &y, &n, &loop, &k)!=EOF)
			{
				for (int i = 0; i < loop; i++)
				{
					clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
					result = modExp(y, k, n);
					clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
					timespec_diff(&start, &end, &interval);
					assert(interval.tv_sec == 0);
					printf("%d %ld\n", k, interval.tv_nsec);
				}
				break;
			}
		case 2 :
			while(fscanf(input, "%d %d %d %d", &y, &n, &loop, &k)!=EOF)
			{
				for (int i = 0; i < loop; i++)
				{
					clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
					result = modExp(y, k, n);
					clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
					timespec_diff(&start, &end, &interval);
					assert(interval.tv_sec == 0);
					printf("%d %ld\n", k, interval.tv_nsec);
				}
				break;
			}
		case 3 :
			while(fscanf(input, "%d %d %d %d", &y, &n, &loop, &k)!=EOF)
			{
				for (int i = 0; i < loop; i++)
				{
					clock_gettime(CLOCK_MONOTONIC_RAW, &start);
					result = modExp(y, k, n);
					clock_gettime(CLOCK_MONOTONIC_RAW, &end);
					timespec_diff(&start, &end, &interval);
					assert(interval.tv_sec == 0);
					printf("%d  %ld\n", k, interval.tv_nsec);
				}
				break;
			}
		case 4 :
			while(fscanf(input, "%d %d %d %d", &y, &n, &loop, &k)!=EOF)
			{
				for (int i = 0; i < loop; i++)
				{
					clock_gettime(CLOCK_MONOTONIC, &start);
					result = modExp(y, k, n);
					clock_gettime(CLOCK_MONOTONIC, &end);
					timespec_diff(&start, &end, &interval);
					assert(interval.tv_sec == 0);
					printf("%d  %ld\n", k, interval.tv_nsec);
				}
				break;
			}
		case 5 :
			while(fscanf(input, "%d %d %d %d", &y, &n, &loop, &k)!=EOF)
			{
				for (int i = 0; i < loop; i++)
				{
					clock_gettime(CLOCK_REALTIME, &start);
					result = modExp(y, k, n);
					clock_gettime(CLOCK_REALTIME, &end);
					timespec_diff(&start, &end, &interval);
					assert(interval.tv_sec == 0);
					printf("%d  %ld\n", k, interval.tv_nsec);
				}
				break;
			}
		default :
			while(fscanf(input, "%d %d %d %d", &y, &n, &loop, &k)!=EOF)
			{
				for (int i = 0; i < loop; i++)
				{
					clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
					result = modExp(y, k, n);
					clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
					timespec_diff(&start, &end, &interval);
					assert(interval.tv_sec == 0);
					printf("%d  %ld\n", k, interval.tv_nsec);
				}
				break;
			}
	}
	fclose(input);
	return 0;
}

int modExp(int y, int k, int n)
{
	int r = 1;
	for (int i = 0; i < 32; i++)
	{
		if (k % 2 == 1)
			r = (r * y) % n;
		y = (y * y) % n;
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
