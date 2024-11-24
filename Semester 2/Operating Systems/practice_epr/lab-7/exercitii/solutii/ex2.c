#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>


// 2. Scrieți un program C care execută o comandă Bash și scrie rezultatul într-un fișier.
// Exemplu: ls -l >lista_fisiere
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
		// creez fisierul
		int fd = open("lista_fisiere", O_CREAT | O_TRUNC | O_RDWR, 0644);
		if (fd == -1)
		{
			perror("open()");
			exit(EXIT_FAILURE);
		}

		// redirectez fluxul de iesire (stdout) in fisier
		dup2(fd, STDOUT_FILENO);
		close(fd);

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
