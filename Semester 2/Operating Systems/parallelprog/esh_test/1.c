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
	int buff[101];
	int length = 0;
	char n;
	printf("Introduceti numere pana la 'x': ");
	while (1) {
		scanf(%c, &n);
		if (n == 'x') {
			
		}
	}
	buff[length] = '\0';
	printf("Am citit ");
	for (int i = 0; i < length; i++)
		printf("%d ", buff[i]);
	printf("\n");
	return 0;
}
