#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "str.h"

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