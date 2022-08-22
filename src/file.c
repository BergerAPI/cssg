#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <bits/stat.h>
#include <dirent.h>
#include "file.h"

char *read_file(char *path) {
    FILE *file = fopen(path, "r");

    if (file == NULL) {
        printf("This file does not exist. %s \n", path);
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

int is_directory(char *path) {
    struct stat statbuf;
    stat(path, &statbuf);
    return S_ISDIR(statbuf.st_mode);
}

int create_directory(char *path) {
    return mkdir(path, 0777);
}

char **get_files_in_directory(char *path) {
    DIR *dir = opendir(path);
    struct dirent *entry;
    char **files = malloc(sizeof(char *) * 100);
    int i = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            files[i] = entry->d_name;
            ++i;
        }
    }
    files[i] = NULL;
    return files;
}

void write_file(char *path, char *content) {
    FILE *file = fopen(path, "wa");

    if (file == NULL) {
        exit(1);
    }

    fwrite(content, 1, strlen(content), file);

    fclose(file);
}