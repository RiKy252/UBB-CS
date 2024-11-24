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
	int sum;
	int fifofd = open("myfifo", O_RDONLY);
	read(fifofd, &sum, sizeof(int));
	close(fifofd);
	printf("Process B prints out the sum: %d\n", sum);
	return 0;
}
