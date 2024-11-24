#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void create_fifo(char *name) {
    if(-1 == mkfifo(name, 0600)) {
        char msg[100];
        sprintf(msg, "Error creating fifo %s", name);
        perror(msg);
        exit(1);
    }
}

void remove_fifo(char *name) {
    if(-1 == unlink(name)) {
        char msg[100];
        sprintf(msg, "Unable to unlink %s", name);
        perror(msg);
    }
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("Please provide at least one argument\n");
        exit(1);
    }
    // create the fifo on the disk
    create_fifo("./a2b");
    // open the fifo
    int a2b = open("./a2b", O_WRONLY);
    if(-1 == a2b) {
        perror("Error on opening fifo a2b");
        exit(1);
    }
    // send the number of arguments that will be sent
    int size = argc - 1;
    if(-1 == write(a2b, &size, sizeof(int))) {
        perror("Error sending argument count");
    } else {
        for(int i = 0; i < size; i++) {
            // first send the data length and then send the data
            int len = strlen(argv[i + 1]);
            if(-1 == write(a2b, &len, sizeof(int))) {
                perror("Error sending length");
            } else {
                if(-1 == write(a2b, argv[i + 1], len * sizeof(char))) {
                    perror("Error sending string");
                }
            }
        }
    }
    close(a2b);
    remove_fifo("./a2b");
    return 0;
}