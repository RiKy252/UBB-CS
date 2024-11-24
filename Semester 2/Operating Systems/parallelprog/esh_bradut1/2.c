#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <ctype.h>

int main(int argc, char* argv[])
{
	char* fifofile = argv[1];
	int pfd[2]; // 
	pipe(pfd);
	int f = fork();
	if (f == -1) {
		perror("Eroare la primul fork\n");
		exit(1);
	}
	if (f == 0) {
		// First child process
		close(pfd[0]);
		int fifofd = open(fifofile, O_RDONLY);
		char ch;
		int sum = 0;
		while (read(fifofd, &ch, 1) > 0) {
			if(isdigit(ch)) {
				// sum += atoi(ch);
				sum += ch - '0';
			}
		}
		close(fifofd);
		write(pfd[1], &sum, sizeof(int));
		close(pfd[1]);
		exit(0);
	}
	else {
		int p2 = fork();
		if (p2 == -1) {
			perror("Eroare la al doilea fork\n");
                	exit(1);
		}
		if (p2 == 0) {
			// Second child process
			close(pfd[1]);
			int sumFromP1;
			read(pfd[0], &sumFromP1, sizeof(int));
			close(pfd[0]);
			for (int d = 1; d * d <= sumFromP1; d++) {
				if (sumFromP1 % d == 0) {
					printf("%d ", d);
					printf("%d ", sumFromP1 / d);
				}
			}
			printf("\n");
		}
		else {
			close(pfd[0]);
			close(pfd[1]);
			wait(NULL);
			wait(NULL);
			unlink(fifofile);
		}
	}
	return 0;
}
