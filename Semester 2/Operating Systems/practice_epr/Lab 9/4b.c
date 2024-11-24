#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
int main(int argc, char *argv[]) {
    // since the other process handles the creation of the fifo, this process needs only to open it
    // open the fifo
    int a2b = open("./a2b", O_RDONLY);
    if(-1 == a2b) {
        perror("Error on opening fifo a2b");
        exit(1);
    }
    int size = 0;
    if(-1 == read(a2b, &size, sizeof(int))) {
        perror("Error reading argument count");
    } else {
        for(int i = 0; i < size; i++) {
            int len = 0;
            if(-1 == read(a2b, &len, sizeof(int))) {
                perror("Error reading length");
            } else {
                // allocate len + 1 bytes to make sure we can place the null terminator
                char *buf = malloc((len + 1) * sizeof(char));
                int k;
                if(-1 == (k = read(a2b, buf, len * sizeof(char)))) {
                    perror("Error sending string");
                } else {
                    buf[k] = 0;
                    printf("Received: %s\n", buf);
                    for(int j = 0; j < k; j++) {
                        buf[j] = toupper(buf[j]);
                    }
                    printf("Result: %s\n", buf);
                }
                free(buf);
            }
        }
    }
    close(a2b);
    return 0;
}
