#include "parameter.h"

std::map<std::string, std::string> parse_argv(char **argv) {
    std::map<std::string, std::string> map;

    int i = 1; // This is one because we want to ignore the path which is position 1

    while (1) {
        char *current_argument = argv[i];

        if (current_argument == nullptr)
            break;

        for (const auto &item: available_parameter)
            if (current_argument == ("-" + item.name)) {
                char *value = argv[++i];

                if (value == nullptr) {
                    printf("You messed up big time. You forgot to provide a value to %s. \n", current_argument);
                    exit(1);
                }

                map[item.name] = value;
            }

        ++i;
    }

    for (const auto &item: available_parameter)
        if (item.required && !map.contains(item.name)) {
            printf("You failed to provide required data.");
            exit(1);
        }

    return map;
}