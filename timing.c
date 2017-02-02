#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/hardirq.h>
#include <linux/preempt.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

int inline modExp(uint32_t k)
{
	int r = 1;
	int y = 50;
	int n = 3;
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

static int __init timing_start(void)
{
	/*int y, n;*/
	/*uint32_t k, loop;*/ /* useless but necessary y */
	uint32_t k[33] = {0, 1, 3, 7, 15, 31, 63, 127, 255, 511, 1023, 2047, 4095, 8191, 16383, 32767, 65535, 131071, 262143, 524287, 1048575, 2097151, 4194303, 8388607, 16777215, 33554431, 67108863, 134217727, 268435455, 536870911, 1073741823, 2147483647, 4294967295};

	int index = 0;
	int i, j;
	unsigned long flags; 
	uint64_t start, end; 
	volatile int variable = 0; 
	unsigned cycles_low, cycles_high, cycles_low1, cycles_high1; 
	
	for (j = 0; j < 33; j++)
	{
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
			
		for (i = 0; i < 1000; i++)
		{
			variable = 0; 
			/*printk(KERN_INFO "Loading test module...\n");*/ 
			preempt_disable(); /*we disable preemption on our CPU*/ 
			raw_local_irq_save(flags); /*we disable hard interrupts on our CPU*/ 
			/*at this stage we exclusively own the CPU*/ 
			
			asm volatile (
				"CPUID\n\t" 
				"RDTSC\n\t" 
				"mov %%edx, %0\n\t" 
				"mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low):: "%rax", "%rbx", "%rcx", "%rdx"); 
			
			/*call the function to measure here*/
			modExp(k[j]);
			
			asm volatile(
				"RDTSCP\n\t" 
				"mov %%edx, %0\n\t" 
				"mov %%eax, %1\n\t" 
				"CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1):: "%rax", "%rbx", "%rcx", "%rdx"); 
			
			raw_local_irq_restore(flags); 
			/*we enable hard interrupts on our CPU*/ 
			preempt_enable();/*we enable preemption*/ 
			start = ( ((uint64_t)cycles_high << 32) | cycles_low ); 
			end = ( ((uint64_t)cycles_high1 << 32) | cycles_low1 ); 
			printk("%d %llu\n", index, (end-start));
    	}
    	index++;
	}
	return 0;
}

module_init(timing_start);
