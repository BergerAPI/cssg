#pragma once

char *read_file(char *path);

int is_directory(char *path);

int create_directory(char *path);

char **get_files_in_directory(char *path);

void write_file(char *path, char *content);