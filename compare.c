#include <stdio.h>
#include <stdlib.h>

int modExp(int y, int k, int n); 
int modExpNTC(int y, int k, int n); 

int main()
{
	int y, k, n, result, resultNTC;
	while(1)
	{
		y = rand();
		k = rand();
		n = rand();
		result = modExp(y, k, n);
		resultNTC = modExpNTC(y, k, n);
		if (result == resultNTC)
		{
			printf("y=%d, k=%d , n=%d . Same. \n", y, k, n);
		}
		else 
		{
			printf("Different! \n");
			return -1;
		}
	}
}

int modExpNTC(int y, int k, int n)
{
	int r = 1;
	int i;
	for (i = 0; i < 32; i++)
	{
		int m;
		m = -(k % 2 == 1);
		r = (m & ((r * y) % n)) | (~m & r);
		y = (y*y) % n;
		k >>= 1;
	}
	return r%n;
}

int modExp(int y, int k, int n)
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
