#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


// 1. Scrieți un program C care execută o comandă Bash și afișează rezultatul pe ecran.
// Exemplu: ls -l
int main(int argc, char* argv[])
{
	// definesc lista de argumente
	char *args[] = {"ls", "-l", NULL};

	// creez un proces copil
	int pid = fork();
	if (pid == -1)
	{
		perror("fork()");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)		// in copil
	{
		// execut comanda
		if (execvp(args[0], args) < 0)
		{
			perror("execvp()");
			exit(EXIT_FAILURE);
		}
	}
	else				// in parinte
	{
		int status;
		wait(&status);	// astept terminarea procesului copil
		printf("[PARINTE] Copil PID %d a returnat %d\n", pid, status);
	}

	return 0;
}
