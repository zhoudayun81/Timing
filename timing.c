#include <stdio.h>
#include <time.h>
#include <stdint.h>

int inline modExp(int y, uint32_t k, int n)
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

int main()
{
	int y, n, loop; /* useless but necessary y */
	uint32_t k;

	FILE *input;
	input = fopen("input", "r");

	int index = 0;
	int i;
 
	uint64_t start, end;
	unsigned cycles_low, cycles_high, cycles_low1, cycles_high1;

			asm volatile (
			"CPUID\n\t" 
			"RDTSC\n\t" 
			"mov %%edx, %0\n\t" 
			"mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low):: "%rax", "%rbx", "%rcx", "%rdx");
		asm volatile(
			"RDTSCP\n\t" 
			"mov %%edx, %0\n\t" 
			"mov %%eax, %1\n\t" 
			"CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1):: "%rax", "%rbx", "%rcx", "%rdx"); 

		asm volatile (
			"CPUID\n\t" 
			"RDTSC\n\t" 
			"mov %%edx, %0\n\t" 
			"mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low):: "%rax", "%rbx", "%rcx", "%rdx");
		asm volatile(
			"RDTSCP\n\t" 
			"mov %%edx, %0\n\t" 
			"mov %%eax, %1\n\t" 
			"CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1):: "%rax", "%rbx", "%rcx", "%rdx"); 
			
	while(fscanf(input, "%d %d %d %u", &y, &n, &loop, &k)!=EOF)
	{
		for (i = 0; i < loop; i++)
		{
			asm volatile (
				"CPUID\n\t" 
				"RDTSC\n\t" 
				"mov %%edx, %0\n\t" 
				"mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low):: "%rax", "%rbx", "%rcx", "%rdx"); 
			
			/*call the function to measure here*/
			modExp(y, k, n);
			
			asm volatile(
				"RDTSCP\n\t" 
				"mov %%edx, %0\n\t" 
				"mov %%eax, %1\n\t" 
				"CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1):: "%rax", "%rbx", "%rcx", "%rdx"); 
 
			start = ( ((uint64_t)cycles_high << 32) | cycles_low ); 
			end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 ); 
			printf("%d %llu\n", index, (end-start));
		}
		index++;
	}
	fclose(input);
	return 0;
}

