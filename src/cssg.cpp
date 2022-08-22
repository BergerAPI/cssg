#include <iostream>
#include <algorithm>

#include "str.h"
#include "file.h"

const std::string TAG_DESCRIPTION = "description:";
const std::string TAG_AUTHOR = "author:";
const std::string TAG_NAME = "name:";

struct Parameter {
    std::string template_path{};
    std::string input{};
};

struct FileInfo {
    std::string name{};
    std::string description{};
    std::string author{};

    int size{};
};

Parameter *parse_argv(char **argv) {
    auto *parameter = new Parameter();

    int i = 1; // This is one because we want to ignore the path which is position 1

    while (1) {
        char *current_argument = argv[i];

        if (current_argument == nullptr)
            break;

        int file = current_argument == std::string("-file");
        int template_path = current_argument == std::string("-template");

        if (file || template_path) {
            char *filePath = argv[++i];

            if (filePath == nullptr) {
                printf("You messed up big time. You forgot to provide a value to %s. \n", current_argument);
                exit(1);
            }

            if (file)
                parameter->input = filePath;
            if (template_path)
                parameter->template_path = filePath;
        }

        ++i;
    }

    if (parameter->input.length() == 0 || parameter->template_path.length() == 0) {
        printf("You failed to provide data.");
        exit(1);
    }

    return parameter;
}

FileInfo *get_head(const std::string content) {
    auto *file_info = new FileInfo();

    int i = 0;
    int ctx = 0;

    char c;
    std::string line = "";

    file_info->size = 0;

    while ((c = content[i++]) != 0) {
        file_info->size++;

        if (c != '\n') {
            line += c;
            continue;
        }


        if (line == "---") {
            if (ctx == 0) {
                ctx = 1;
                line = "";
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

            if (line.starts_with(TAG_NAME))
                file_info->name = str_trim(line.substr(TAG_NAME.length(), line.length()));

            if (line.starts_with(TAG_DESCRIPTION))
                file_info->description = str_trim(line.substr(TAG_DESCRIPTION.length(), line.length()));

            if (line.starts_with(TAG_AUTHOR))
                file_info->author = str_trim(line.substr(TAG_AUTHOR.length(), line.length()));
        }

        line = "";
    }

    return file_info;
}

std::string generate_html(FileInfo *i, std::string &content, std::string template_content) {
    printf("Name: %s \n", i->name.c_str());
    printf("Description: %s \n", i->description.c_str());
    printf("Author: %s \n", i->author.c_str());

    content = content.substr(i->size, content.length());

    template_content = replaceAll(template_content, "{{name}}", i->name);
    template_content = replaceAll(template_content, "{{description}}", i->description);
    template_content = replaceAll(template_content, "{{author}}", i->author);
    template_content = replaceAll(template_content, "{{content}}", content);

    return template_content;
}

void process_file(std::string &template_content, std::string &file_path) {
    std::string file_content = read_file(file_path);

    FileInfo *file_info = get_head(file_content);
    std::string file_name = replaceAll(file_info->name, " ", "-") + ".html";

    std::transform(file_name.begin(), file_name.end(), file_name.begin(), ::tolower);

    // Some cool debug information
    std::cout << "Path: " << file_path << std::endl;

    write_file(file_name, generate_html(file_info, file_content, template_content));

    std::cout << "---" << std::endl;
}

int main(__attribute__((unused)) int argc, char **argv) {
    Parameter *p = parse_argv(argv);

    std::string template_content = read_file(p->template_path);

    if (is_directory(p->input))
        for (std::string value: get_files_in_directory(p->input))
            process_file(template_content, value);
    else process_file(template_content, p->input);

    std::cout << "Successfully generated the pages." << std::endl;

    return 0;
}