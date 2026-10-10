#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    int fd;
    char buffer[100];

    fd = open("input.txt", O_RDONLY);
    if (fd == -1) { perror("open"); exit(EXIT_FAILURE); }

    dup2(fd, STDIN_FILENO);
    close(fd);

    printf("Reading from redirected standard input:\n");
    while (fgets(buffer, sizeof(buffer), stdin) != NULL)
        printf("%s", buffer);

    return 0;
}
