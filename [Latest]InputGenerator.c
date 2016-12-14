#include <stdio.h>
#include <stdlib.h> 
#include <stdint.h>

int main( int argc, char *argv[] )
{
if(argc<5)
{
fprintf(stderr, "Usage: <first argument &y> <second argument &n> <times to execute one secret key &loop> <secret key index [from 0-32]>... \n");
exit(-1);
}else if(argc>37)
{
fprintf(stderr, "Overcrowded arguments! \n");
exit(-1);
}
uint32_t KEY[33] = {0, 1, 3, 7, 15, 31, 63, 127, 255, 511, 1023, 2047, 4095, 8191, 16383, 32767, 65535, 131071, 262143, 524287, 1048575, 2097151, 4194303, 8388607, 16777215, 33554431, 67108863, 134217727, 268435455, 536870911, 1073741823, 2147483647, 4294967295};
int y, n; /* useless but necessary y and n */
y = atoi(argv[1]);
n = atoi(argv[2]);
uint32_t loop;
loop = atoi(argv[3]);

FILE *generate_input;
/*generate input feed file*/
generate_input = fopen("input", "w");
for(int i = 4; i < argc; i++)
{
  int index = atoi(argv[i]);
  if(index>=33)
  {
  fprintf(stderr, "Index out of boundary!\n Program ignored that index!\n");
  continue;
  }
  uint32_t key = KEY[index];
  fprintf(generate_input, "%d %d %u %u\n", y, n, loop, key);
}
fclose(generate_input);
printf("Finished! \n");
exit(0);
}
