#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "file.h"

char *read_file(char *path) {
    FILE *file = fopen(path, "r");

    if (file == NULL) {
        printf("This file does not exist. \n");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0, SEEK_SET);  /* same as rewind(file); */

    char *content = malloc(fsize + 1);
    fread(content, fsize, 1, file);
    fclose(file);

    return content;
}

void write_file(char *path, char *content) {
    FILE *file = fopen(path, "wa");

    if (file == NULL) {
        exit(1);
    }

    fwrite(content, 1, strlen(content), file);

    fclose(file);
}