#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int arcg, char *argv[]) {
    int c_12p[2], c_22p[2];
    int p2c_1[2], p2c_2[2];
    if(-1 == pipe(c_12p)) {
        perror("Error creating pipe from first child to parent");
        exit(1);
    }
    if(-1 == pipe(c_22p)) {
        perror("Error creating pipe from second child to parent");
        exit(1);
    }
    if(-1 == pipe(p2c_1)) {
        perror("Error creating pipe from parent to the first child");
        exit(1);
    }
    if(-1 == pipe(p2c_2)) {
        perror("Error creating pipe from parent to the second child");
        exit(1);
    }
    int f1 = fork();
    if(-1 == f1) {
        perror("Error creating the first child");
    } else if (0 == f1) {
        srand(getpid());
        close(c_22p[0]); // pipe c_22p is used by the other child, can be closed safely here
        close(c_22p[1]);
        close(p2c_2[0]); // pipe p2c_2 is sending data to the other child process, we don't need it here
        close(p2c_2[1]);

        close(c_12p[0]); // close the reading end of this pipe
        close(p2c_1[1]); // close the writing end of the pipe from parent
        int nr = rand() % 1000;
        printf("Child 1 generated %d\n", nr);
        if(-1 == write(c_12p[1], &nr, sizeof(int))) {
            perror("Error sending first number to parent");
            close(c_12p[1]);
            close(p2c_1[0]);
            exit(1);
        }
        if(-1 == read(p2c_1[0], &nr, sizeof(int))) {
            perror("Error reading result from parent");
            close(c_12p[1]);
            close(p2c_1[0]);
            exit(1);
        }
        if(nr == 1) {
            printf("Child 1 won!\n");
        } else if (nr == 0) {
            printf("Draw!\n");
        } else {
            printf("Child 1 lost!\n");
        }
        close(p2c_1[0]);
        close(c_12p[1]);
        exit(0);
    }

    int f2 = fork();
    if(-1 == f2) {
        perror("Error creating the second child");
    } else if (0 == f2) {
        srand(getpid());
        close(c_12p[0]); // pipe c_12p is used by the other child
        close(c_12p[1]);
        close(p2c_1[0]); // pipe p2c_1 is sending data to the other child process, we don't need it here
        close(p2c_1[1]);

        close(c_22p[0]); // close the reading end of this pipe
        close(p2c_2[1]); // close the writing end of the pipe from parent
        int nr = rand() % 1000;
        printf("Child 2 generated %d\n", nr);
        if(-1 == write(c_22p[1], &nr, sizeof(int))) {
            perror("Error sending second number to parent");
            close(c_22p[1]);
            close(p2c_2[0]);
            exit(1);
        }
        if(-1 == read(p2c_2[0], &nr, sizeof(int))) {
            perror("Error reading result from parent");
            close(c_22p[1]);
            close(p2c_2[0]);
            exit(1);
        }
        if(nr == 1) {
            printf("Child 2 won!\n");
        } else if (nr == 0) {
            printf("Draw!\n");
        } else {
            printf("Child 2 lost!\n");
        }
        close(p2c_2[0]);
        close(c_22p[1]);
        exit(0);
    }
    close(c_12p[1]);
    close(c_22p[1]);
    close(p2c_1[0]);
    close(p2c_2[0]);
    int nr1, nr2;
    if(-1 == read(c_12p[0], &nr1, sizeof(int))) {
        perror("Error reading first number");
        close(c_12p[0]);
        close(c_22p[0]);
        close(p2c_1[1]);
        close(p2c_2[1]);
        wait(0);
        wait(0);
        exit(1);
    }
    if(-1 == read(c_22p[0], &nr2, sizeof(int))) {
        perror("Error reading second number");
        close(c_12p[0]);
        close(c_22p[0]);
        close(p2c_1[1]);
        close(p2c_2[1]);
        wait(0);
        wait(0);
        exit(1);
    }
    printf("First number %d\nSecond number %d\n", nr1, nr2);
    if(nr1 > nr2) {
        nr1 = 1;
        nr2 = -1;
    } else if (nr1 == nr2) {
        nr1 = 0;
        nr2 = 0;
    } else {
        nr1 = -1;
        nr2 = 1;
    }
    if(-1 == write(p2c_1[1], &nr1, sizeof(int))) {
        perror("Error sending first response");
        close(c_12p[0]);
        close(c_22p[0]);
        close(p2c_1[1]);
        close(p2c_2[1]);
        wait(0);
        wait(0);
        exit(1);
    }
    if(-1 == write(p2c_2[1], &nr2, sizeof(int))) {
        perror("Error sending second response");
        close(c_12p[0]);
        close(c_22p[0]);
        close(p2c_1[1]);
        close(p2c_2[1]);
        wait(0);
        wait(0);
        exit(1);
    }
    close(c_12p[0]);
    close(c_22p[0]);
    close(p2c_1[1]);
    close(p2c_2[1]);
    wait(0);
    wait(0);
    return 0;
}