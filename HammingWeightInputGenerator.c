#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

uint32_t HammingWeightGenerator(int hammingWeight);
int isIn(int index, int array[], int size);

int main()
{
	/* useless but necessary y and n */
	int y =50;
	int n = 3;
	
	/*generate random inputs feed file*/
	FILE * input;
	input = fopen("input", "w");
	
	uint32_t key;
	key = HammingWeightGenerator(5);
	fprintf(input, "%d %d 10000 %u\n", y, n, key);
	
	key = HammingWeightGenerator(25);
	fprintf(input, "%d %d 10000 %u\n", y, n, key);
	
	fclose(input);
	printf("Finished! \n");
	
	return 0;
}

uint32_t HammingWeightGenerator(int hammingWeight)
{
	uint32_t key = 0;
	int indexRecorder[hammingWeight];
	int index;
	int i=0;
	while(i < hammingWeight)
	{
		srand(time(NULL));
		index = rand() % 32;
		if(isIn(index, indexRecorder, i))
			continue;
		indexRecorder[i] = index;
		key += pow(2, indexRecorder[i]);
		i++;
	}
	return key;
}

int isIn(int index, int array[], int size)
{
	for (int i = 0; i < size; i++) 
	{
		if (index == array[i])
			return 1;
	}
	return 0;
}
