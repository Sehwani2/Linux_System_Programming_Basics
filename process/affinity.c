#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sched.h>
#include <sys/types.h>

#define MAXCPU	2
static void print_cpuset(cpu_set_t *mask)
{
	int i;

	for(i=0;i<MAXCPU;i++){
		if(CPU_ISSET(i,mask)){
			printf("CPU%d",i);
		}
	}
	printf("\n");
}
int main(int argc, char** argv)
{
	cpu_set_t mask;
	int cur;

	if(sched_getaffinity(getpid(), sizeof(cpu_set_t),&mask)){
		perror("sched_getaffinity()\n");
		return -1;
	}
	print_cpuset(&mask);
	
	cur = sched_getcpu();
	printf("run on CPU%d\n",cur);

	CPU_ZERO(&mask);
	CPU_SET(cur ^ 1, &mask);
	if(sched_setaffinity(getpid(),sizeof(cpu_set_t),&mask)){
		perror("sched_setaffinity()\n");
		return -1;
	}
	sleep(1);

	cur = sched_getcpu();
	printf("run on CPU%d\n",cur);
	return 0;
}
