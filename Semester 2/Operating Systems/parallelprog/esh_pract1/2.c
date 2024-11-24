#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	if (argc != 2) {
		perror("Please insert exactly one argument!\n");
		exit(1);
	}
	int n = atoi(argv[1]);
	for (int i = 1; i <= n; i++) {
		int f = fork();
		if (f == -1) {
			perror("Error on fork!\n");
		}
		else if (f == 0) { 			// child process
			printf("Child process %d - PID: %d - PPID %d\n", i, getpid(), getppid());
		}
		else { 					// parent process
			printf("Parent %d - Child: %d\n", getpid(), f);
			wait(0);
			exit(0);
		}
	}
	return 0;
}
