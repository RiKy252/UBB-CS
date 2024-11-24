#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	int p = 0;	
	for (int i = 0; i < 3; i++) {
		if (p == 0) {
			p = fork();
		}
		else {
			wait(0);
		}
	}
	printf("PID = %d, PPID = %d, p = %d\n", getpid(), getppid(), p);
	return 0;
}
