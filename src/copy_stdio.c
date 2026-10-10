#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 8192

int main(int argc, char *argv[]) {
    FILE *src, *dest;
    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    if (argc != 3) { fprintf(stderr, "Usage: %s <src> <dest>\n", argv[0]); return 1; }

    src = fopen(argv[1], "rb");
    if (!src) { perror("fopen src"); return 1; }

    dest = fopen(argv[2], "wb");
    if (!dest) { perror("fopen dest"); fclose(src); return 1; }

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, src)) > 0) {
        size_t written = 0;
        while (written < bytes_read) {
            size_t w = fwrite(buffer + written, 1, bytes_read - written, dest);
            if (w == 0 && ferror(dest)) { perror("fwrite"); fclose(src); fclose(dest); return 1; }
            written += w;
        }
    }

    fseek(src, 0, SEEK_END);
    long file_size = ftell(src);
    if (file_size >= 0) printf("Source file size: %ld bytes\n", file_size);

    fclose(src); fclose(dest);
    printf("File copied successfully.\n");
    return 0;
}
