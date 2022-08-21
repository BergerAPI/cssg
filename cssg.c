#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

int str_starts_with(char *prefix, char *content) {
    return strncmp(prefix, content, strlen(prefix)) == 0;
}

char *str_substring(int f, int t, char *content) {
    char *sub = malloc(sizeof(char) * (t - f));
    int c = 0;

    while (c < t - f) {
        sub[c] = content[f + c - 1];
        c++;
    }

    sub[c] = '\0';

    return sub;
}

char *str_trim(char *str) {
    char *end;

    while (isspace((unsigned char) *str)) str++;

    if (*str == 0)
        return str;

    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char) *end)) end--;

    end[1] = '\0';

    return str;
}

char *str_replace(char *orig, char *rep, char *with) {
    char *result;
    char *ins;
    char *tmp;
    int len_rep;
    int len_with;
    int len_front;
    int count;

    if (!orig || !rep)
        return NULL;

    len_rep = strlen(rep);

    if (len_rep == 0)
        return NULL;

    if (!with)
        with = "";

    len_with = strlen(with);
    ins = orig;

    for (count = 0; tmp = strstr(ins, rep); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep;
    }

    strcpy(tmp, orig);

    return result;
}

char *str_lower(char *content) {
    for (int i = 0; content[i]; i++)
        content[i] = tolower(content[i]);

    return content;
}

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