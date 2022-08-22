#pragma once

int str_starts_with(char *prefix, char *content);

char *str_substring(size_t f, size_t t, const char *content);

char *str_trim(char *str);

char *str_replace(char *orig, char *rep, char *with);

char *str_lower(char *content);