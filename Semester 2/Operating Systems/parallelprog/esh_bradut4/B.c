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
	// B process
	int fifofd = open("fifo", O_RDONLY);
	char ch;
	read(fifofd, &ch, sizeof(char));
	close(fifofd);
	printf("[B] Read character %c and closed the fifo\n", ch);
	unlink("fifo");
	printf("[B] Deleted the fifo\n");
	int n = (int)ch;
	printf("[B] The ascii code of %c is %d\n", ch, n);
	return 0;
}
