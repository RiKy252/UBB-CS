#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>


// 3. Scrieți un program C care execută două comenzi Bash conectate prin pipe.
// Exemplu: ls -l | wc -l
int main(int argc, char* argv[])
{
	// definesc listele de argumente
	char *first_cmd[] = {"ls", "-l", NULL};
	char *second_cmd[] = {"wc", "-l", NULL};

	// creez un pipe
	int pd[2];
	if (pipe(pd) < 0)
	{
		perror("pipe()");
		exit(EXIT_FAILURE);
	}

	// creez primul proces copil
	int pid1 = fork();
	if (pid1 == -1)
	{
		perror("fork()");
		exit(EXIT_FAILURE);
	}

	// in procesul copil
	if (pid1 == 0)
	{
		// inchid capatul de citire din pipe
		close(pd[0]);

		// conectez fluxul de iesire (stdout) la capatul de scriere in pipe
		dup2(pd[1], STDOUT_FILENO);
		close(pd[1]);

		// execut comanda
		if (execvp(first_cmd[0], first_cmd) < 0)
		{
			perror("execvp()");
			exit(EXIT_FAILURE);
		}
	}

	// creez al doilea proces copil
    int pid2 = fork();
    if (pid2 == -1)
    {
        perror("fork()");
        exit(EXIT_FAILURE);
    }

	// in procesul copil
    if (pid2 == 0)
    {
        // inchid capatul de scriere in pipe
        close(pd[1]);

        // conectez capatul de citire din pipe la fluxul de intrare (stdin)
        dup2(pd[0], STDIN_FILENO);
        close(pd[0]);

        // execut comanda
        if (execvp(second_cmd[0], second_cmd) < 0)
        {
            perror("execvp()");
            exit(EXIT_FAILURE);
        }
    }

	// in parinte
	close(pd[0]);				// inchid capatul de citire
	close(pd[1]);				// inchid capatul de scriere

	int status;
	waitpid(pid1, &status, 0);	// astept terminarea primului proces copil
	printf("[PARINTE] Copil PID %d a returnat %d\n", pid1, status);
	waitpid(pid2, &status, 0);	// astept terminarea celui de-al doilea proces copil
	printf("[PARINTE] Copil PID %d a returnat %d\n", pid2, status);

	return 0;
}
