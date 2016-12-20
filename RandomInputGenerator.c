#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

int main(int argc, char* argv[])
{
	if(argc != 5)
	{
		fprintf(stderr, "Usage: <y> <n> <loop> <number of keys> \n");
	}

	/* useless but necessary y and n */
	uint32_t y = atoi(argv[1]);
	uint32_t n = atoi(argv[2]);
	uint32_t loop = atoi(argv[3]);
	int num_key = atoi(argv[4]);

	/*generate random inputs feed file*/
	FILE * input;
	input = fopen("input", "w");

	uint32_t key;
	srand((unsigned) time(NULL));
	for (int i = 0; i < num_key; i++)
	{
		key = rand();
		fprintf(input, "%u %u %u %u\n", y, n, loop, key);
	}
	fclose(input);
	printf("Finished! \n");

	return 0;
}

