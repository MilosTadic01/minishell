#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;

    // Create a temporary file without a name (O_TMPFILE)
    fd = open(".", O_RDWR | O_TMPFILE | O_CREAT | O_EXCL, 0644);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    dprintf(fd, "Hello world\n");

    // Close the file descriptor
    close(fd);

    return 0;
}
