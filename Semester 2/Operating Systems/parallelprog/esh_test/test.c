#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/stat.h>

int main(int argc, char* argv[])
{
	int pfd1[2]; // P1 -> P2
	if (pipe(pfd1) == -1) {
		perror("Error creating pipe from P1 to P2\n");
		exit(1);
	}
	int p1 = fork();
	if (p1 == -1) {
		perror("Error on forking the first process!\n");
		exit(1);
	}
	if (p1 == 0) {
		// P1 process
		close(pfd1[0]);
		FILE* file;
        	char filename[101];
        	printf("[P1] Numele fisierului: ");
        	scanf("%s", filename);
        	printf("[P1] Primit: %s\n", filename);
		printf("[P1] Cate numere sa citesc din fisier: ");
		int n;
        	scanf("%d", &n);
        	file = fopen(filename, "r");
        	int numbers[101];
        	int count = 0;
        	while (fscanf(file, "%d", &numbers[count]) == 1 && count < n)
        	{
                	printf("[P1] Am citit numarul %d\n", numbers[count]);
                	count++;
        	}
        	fclose(file);
		write(pfd1[1], &count, sizeof(int));
		printf("[P1] I've sent the count in pipe for P2\n");
		write(pfd1[1], numbers, sizeof(int) * count);
		close(pfd1[1]);
		printf("[P1] I've sent the count and numbers in pipe for P2\n");
		exit(0);
	}
	else {
		int p2 = fork();
		if (p2 == -1) {
			perror("Error on forking the second process!\n");
			exit(1);
		}
		if (p2 == 0) {
			// P2 process
			close(pfd1[1]);
			int count;
			int numbers[101];
			read(pfd1[0], &count, sizeof(int));
			printf("[P2] I read the count: %d\n", count);
			read(pfd1[0], numbers, sizeof(int) * count);
			printf("[P2] I read the numbers\n");
			close(pfd1[0]);
			int sum = 0;
			for (int i = 0; i < count; i++) {
				if (numbers[i] % 2 == 1) {
					sum += numbers[i];
					printf("[P2] Sum = %d\n", sum);
				}
			}
			int fifofd = open("myfifo", O_WRONLY);
			write(fifofd, &sum, sizeof(int));
			printf("[P2] I've sent the sum in fifo\n");
			close(fifofd);
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
