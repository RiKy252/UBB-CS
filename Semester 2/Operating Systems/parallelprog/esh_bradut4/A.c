#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/stat.h>

int main(int argc, char* argv[])
{
	int pfd[2]; // P1 -> P2
	if (pipe(pfd) == -1) {
		perror("Error on creating pipe from P1 to P2\n");
		exit(1);
	}
	int p1 = fork();
	if (p1 == -1) {
		perror("Error on forking P1\n");
		exit(1);
	}
	if (p1 == 0) {
		// P1 Process
		close(pfd[0]);
		FILE* file = fopen("text", "r");
		int n;
		printf("[P1] Enter the number: ");
		scanf("%d", &n);
		printf("[P1] Read the number %d\n", n);
		char line[201];
		int count = 0;
		char ch;
		while (fgets(line, sizeof(line), file) && count < n) {
			for (int i = 0; i < strlen(line); i++) {
				if (line[i] != '\n') {
					count++;
					ch = line[i];
					if (count == n)
						break;
				}
			}
		}
		printf("[P1] Character number %d: %c\n", n, ch);
		fclose(file);
		write(pfd[1], &ch, sizeof(char));
		close(pfd[1]);
		printf("[P1] I've done my job!\n");
		exit(0);
	}
	else {
		int p2 = fork();
		if (p2 == -1) {
			perror("Error on forking P2\n");
			exit(1);
		}
		if (p2 == 0) {
			// P2 Process
			close(pfd[1]);
			char ch;
			read(pfd[0], &ch, sizeof(char));
			close(pfd[0]);
			printf("[P2] I've received the character %c from P1\n", ch);
			if (('0' <= ch) && (ch <= '9')) {
				printf("[P2] The character %c is a digit\n", ch);
			}
			else if ((('a' <= ch) && (ch <= 'z')) || (('A' <= ch) && (ch <= 'Z'))) {
				printf("[P2] The character %c is a letter\n", ch);
			}
			else
				printf("[P2] The character %c is a special character\n", ch);
			mkfifo("fifo", 0600);
			printf("[P2] Created the fifo\n");
			int fifofd = open("fifo", O_WRONLY);
			printf("[P2] Opened the fifo in write only mode\n");
			write(fifofd, &ch, sizeof(char));
			printf("[P2] Wrote to the fifo the character %c\n", ch);
			close(fifofd);
			printf("[P2] I've done my job\n");
			exit(0);
		}
		else {
			// Parent process
			wait(NULL);
			wait(NULL);
			printf("[Parent] I've waited for my childs!\n");
		}
	}
	return 0;
}
