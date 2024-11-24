#include<stdarg.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc, char **argv)
{
	printf("Start...\n");

	int x = 7;

	// int child = fork();

	// printf("PID = %d PPID = %d ...End\n", getpid(), getppid());

	if (!fork()) {
		printf("PID = %d x = %d\n", getpid(), x);
		x = x * 3 - 9;
		printf("PID = %d x = %d\n", getpid(), x);
		exit(0);
	}
	
		
	printf("PID = %d x = %d\n", getpid(), x);

	x = (x - 4) * 3;

	printf("PID = %d x = %d\n", getpid(), x);
	
	
	return 0;
}
