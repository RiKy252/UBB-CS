#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	if (argc != 2) {
		perror("Please provide exactly one argument!\n");
		exit(1);
	}
	int n = atoi(argv[1]);
	for (int i = 0; i < n; i++) {
		int f = fork();
		if (f == -1) {
			perror("Error on fork!\n");
		}
		else if (f == 0) { 		// child process
			printf("Child process %d - PID: %d - PPID: %d\n", i, getpid(), getppid());
			exit(0);	
		}
		else {				// parent process
			printf("Parent %d - Child: %d\n", getpid(), f);
		}
	}
	for (int i = 0; i < n; i++)
		wait(NULL);
	return 0;
}
