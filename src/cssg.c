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
    Parameter *p = malloc(sizeof(Parameter));

    int i = 1; // This is one because we want to ignore the path which is position 1

    while (1) {
        char *c = argv[i];

        if (c == NULL)
            break;

        int file = strcmp(c, "-file") == 0;
        int template = strcmp(c, "-template") == 0;

        if (file || template) {
            char *v = argv[++i];

            if (v == NULL) {
                printf("You messed up big time. You forgot to provide a value to %s. \n", c);
                exit(1);
            }

            if (file)
                p->file = v;
            if (template)
                p->template = v;
        }

        ++i;
    }

    if (p->file == NULL || p->template == NULL) {
        printf("You failed to provide data.");
        exit(1);
    }

    return p;
}

FileInfo *get_head(const char *content) {
    FileInfo *info = malloc(sizeof(FileInfo));

    int i = 0;
    int ctx = 0;

    char c;
    char *l = "";

    info->size = 0;

    while ((c = content[i++]) != NULL) {
        info->size += 1;

        if (c != '\n') {
            int len = strlen(l);
            char buf[len + 2];

            strcpy(buf, l);
            buf[len] = c;
            buf[len + 1] = 0;

            l = strdup(buf);

            continue;
        };


        if (strcmp(l, "---") == 0) {
            if (ctx == 0) {
                ctx = 1;
                l = "";
                continue;
            }

            break;
        }

        // We're in a context were the head is defined
        // This head looks like this
        //
        // name: niclas
        // description: ...
        // ...
        if (ctx) {
            int offset = 1; // Real length of the string, otherwise we'll get that ':' too

            if (str_starts_with(TAG_NAME, l))
                info->name = str_trim(str_substring(strlen(TAG_NAME) + offset, strlen(l) + 1, l));

            if (str_starts_with(TAG_DESCRIPTION, l))
                info->description = str_trim(str_substring(strlen(TAG_DESCRIPTION) + offset, strlen(l) + 1, l));

            if (str_starts_with(TAG_AUTHOR, l))
                info->author = str_trim(str_substring(strlen(TAG_AUTHOR) + offset, strlen(l) + 1, l));
        }

        l = "";
    }

    return info;
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

    FileInfo *i = get_head(content);
    char *file_name = str_lower(strcat(str_replace(i->name, " ", "-"), ".html"));

    write_file(file_name, generate_html(i, content, template));

    free(p);

    return 0;
}