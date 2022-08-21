#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "file.h"

char *read_file(char *path) {
    FILE *f = fopen(path, "r");

    if (f == NULL) {
        printf("This file does not exist. \n");
        exit(1);
    }

    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);  /* same as rewind(f); */

    char *c = malloc(fsize + 1);
    fread(c, fsize, 1, f);
    fclose(f);

    return c;
}

void write_file(char *path, char *content) {
    FILE *f = fopen(path, "wa");

    if (f == NULL) {
        exit(1);
    }

    fwrite(content, 1, strlen(content), f);

    fclose(f);
}