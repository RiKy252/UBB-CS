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
	char* fifofile = argv[1];	
	char fileName[101];
	printf("Enter the filename: ");
	fgets(fileName, 101, stdin);
	fileName[strlen(fileName) - 1] = '\0';
	// int n = strlen(fileName) + 1;
	FILE* file= fopen(fileName, "r");
	if (file == NULL) {
		perror("Error at opening the file\n");
		exit(1);
	}
	if (mkfifo(fifofile, 0777) == -1) {
		perror("Error making fifo!\n");
		exit(1);
	}
	int fifofd = open(fifofile, O_WRONLY);
	if (fifofd == -1) {
		perror("Eroare la deschiderea FIFO");
        	fclose(file);
        	exit(1);
	}
	char line[256];
	while (fgets(line, sizeof(line), file)) {
		for (int i = 0; line[i] != '\0'; i++) {
			if (isdigit((unsigned char)line[i])) {
				if (write(fifofd, &line[i], sizeof(char)) == -1) {
					perror("Eroare la scrierea in FIFO\n");
					close(fifofd);
					fclose(file);
					exit(1);
				}	
			}
		}
	}
	close(fifofd);
	fclose(file);
	return 0;
}	
