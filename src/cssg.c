#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "str.h"
#include "file.h"

#define TAG_DESCRIPTION "description:"
#define TAG_AUTHOR "author:"
#define TAG_NAME "name:"

typedef struct {
    char *template;
    char *file;
} Parameter;

typedef struct {
    char *name;
    char *description;
    char *author;

    int size;
} FileInfo;

Parameter *parse_argv(char **argv) {
    Parameter *parameter = malloc(sizeof(Parameter));

    int i = 1; // This is one because we want to ignore the path which is position 1

    while (1) {
        char *current_argument = argv[i];

        if (current_argument == NULL)
            break;

        int file = strcmp(current_argument, "-file") == 0;
        int template = strcmp(current_argument, "-template") == 0;

        if (file || template) {
            char *filePath = argv[++i];

            if (filePath == NULL) {
                printf("You messed up big time. You forgot to provide a value to %s. \n", current_argument);
                exit(1);
            }

            if (file)
                parameter->file = filePath;
            if (template)
                parameter->template = filePath;
        }

        ++i;
    }

    if (parameter->file == NULL || parameter->template == NULL) {
        printf("You failed to provide data.");
        exit(1);
    }

    return parameter;
}

FileInfo *get_head(const char *content) {
    FileInfo *file_info = malloc(sizeof(FileInfo));

    int i = 0;
    int ctx = 0;

    char line;
    char *l = "";

    file_info->size = 0;

    while ((line = content[i++]) != 0) {
        file_info->size++;

        if (line != '\n') {
            unsigned int len = strlen(l);
            char buf[len + 2];

            strcpy(buf, l);
            buf[len] = line;
            buf[len + 1] = 0;

            l = strdup(buf);
            continue;
        }


        if (strcmp(l, "---") == 0) {
            if (ctx == 0) {
                ctx = 1;
                l = "";
                continue;
            }

            break;
        }

        // We're in a context where the head is defined
        // This head looks like this
        //
        // name: niclas
        // description: ...
        // ...
        if (ctx) {
            int offset = 1; // Real length of the string, otherwise we'll get that ':' too

            if (str_starts_with(TAG_NAME, l))
                file_info->name = str_trim(str_substring(strlen(TAG_NAME) + offset, strlen(l) + 1, l));

            if (str_starts_with(TAG_DESCRIPTION, l))
                file_info->description = str_trim(str_substring(strlen(TAG_DESCRIPTION) + offset, strlen(l) + 1, l));

            if (str_starts_with(TAG_AUTHOR, l))
                file_info->author = str_trim(str_substring(strlen(TAG_AUTHOR) + offset, strlen(l) + 1, l));
        }

        l = "";
    }

    return file_info;
}

char *generate_html(FileInfo *i, char *content, char *template) {
    printf("Name: %s \n", i->name);
    printf("Description: %s \n", i->description);
    printf("Author: %s \n", i->author);

    content = str_substring(i->size, strlen(content) + 1, content);

    template = str_replace(template, "{{name}}", i->name);
    template = str_replace(template, "{{description}}", i->description);
    template = str_replace(template, "{{author}}", i->author);
    template = str_replace(template, "{{content}}", content);

    return template;
}

int main(__attribute__((unused)) int argc, char **argv) {
    Parameter *p = parse_argv(argv);

    char *content = read_file(p->file);
    char *template = read_file(p->template);

    FileInfo *fileInfo = get_head(content);
    char *file_name = str_lower(strcat(str_replace(fileInfo->name, " ", "-"), ".html"));

    write_file(file_name, generate_html(fileInfo, content, template));

    free(p);

    return 0;
}