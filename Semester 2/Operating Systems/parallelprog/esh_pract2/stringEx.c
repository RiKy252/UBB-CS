#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
	int fd[2];
	if (pipe(fd) == -1) {
		perror("Error creating pipe\n");
		exit(1);
	}
	int f = fork();
	if (f == -1) {
		perror("Error forking\n");
		exit(1);
	}
	if (f == 0) {
		// Child process
		char str[200];
		close(fd[0]);
		printf("Input string: ");
		
		fgets(str, 200, stdin);
		str[strlen(str) - 1] = '\0';
		int n = strlen(str) + 1;

		if (write(fd[1], &n, sizeof(int)) == -1) {
			perror("Error sending size of array through pipe!\n");
			exit(1);
		}

		if (write(fd[1], str, strlen(str) + 1) == -1) {
			perror("Error sending array through pipe!\n");
			exit(1);
		}
		close(fd[1]);
	}
	else {
		// Parent process
		close(fd[1]);
		char str[200];
		int n;
		read(fd[0], &n, sizeof(int));
		read(fd[0], str, n);
		printf("Received %s\n", str);
		close(fd[0]);
		wait(NULL);
	}
	return 0;
}
