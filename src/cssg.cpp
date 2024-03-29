#include <iostream>
#include <algorithm>
#include <map>

#include "str.h"
#include "file.h"
#include "parameter.h"

/* Information about a markdown file */
struct FileInfo {
    std::map<std::string, std::string> values;

    /* How big the head is */
    int size{};
};

/* All tags that one can use in their markdown file */
const std::vector<std::string> available_tags = {
        "name",
        "description",
        "author"
};

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
        if (ctx)
            for (const auto &item: available_tags)
                if (line.starts_with(item))
                    file_info->values[item] = str_trim(line.substr(item.length() + 1, line.length()));

        line = "";
    }

    return file_info;
}

std::string generate_html_header(FileInfo *i) {
    std::string result;

    result.append("<meta name=\"description\" content=\"" + i->values["description"] + "\">\n");
    result.append("<title>" + i->values["name"] + "</title>");

    // For Social-Media (Discord, Skype, Twitter etc.)
    result.append("<meta property=\"og:title\" content=\"" + i->values["name"] + "\" />\n");
    result.append("<meta property=\"og:description\" content=\"" + i->values["description"] + "\" />\n");
    result.append("<meta name=\"theme-color\" content=\"#FF0000\">\n");
    result.append("<meta property=\"og:type\" content=\"website\" />\n");

    return result;
}

std::string generate_html(FileInfo *i, std::string &content, std::string template_content) {
    content = content.substr(i->size, content.length());

    for (const auto &item: i->values)
        template_content = replaceAll(template_content, "{{" + item.first + "}}", item.second);

    template_content = replaceAll(template_content, "{{content}}", content);
    template_content = replaceAll(template_content, "{{head}}", generate_html_header(i));

    return template_content;
}

void debug_log(std::string path, FileInfo *i) {
    std::cout << "path: " << path << std::endl;

    for (const auto &item: i->values)
        std::cout << (item.first + ": " + item.second) << std::endl;

    std::cout << "---" << std::endl;
}

std::string get_html_file_name(FileInfo *fileInfo) {
    std::string file_name = replaceAll(fileInfo->values["name"], " ", "-") + ".html";
    std::transform(file_name.begin(), file_name.end(), file_name.begin(), ::tolower);

    return file_name;
}

void process_file(std::string &template_path, std::string &file_path) {
    std::string file_content = read_file(file_path);
    std::string template_content = read_file(template_path);

    FileInfo *file_info = get_head(file_content);
    std::string file_name = get_html_file_name(file_info);

    write_file("./out/posts/" + file_name, generate_html(file_info, file_content, template_content));
    debug_log(file_path, file_info);
}

int main(__attribute__((unused)) int argc, char **argv) {
    auto p = parse_argv(argv);

    auto input = p["input"];
    auto postTemplate = p["post-template"];
    auto indexTemplate = p["index-template"];

    auto posts = get_files_in_directory(input);

    // Creating the out directory
    create_directory("out", true);
    create_directory("out/posts");

    if (is_directory(input))
        for (std::string value: posts)
            process_file(postTemplate, value);
    else process_file(postTemplate, input);

    /* Creates an index file, containing all posts */
    if (p.contains("index-template")) {
        std::string index_content = read_file(indexTemplate);
        std::string list_string = "";

        std::for_each(posts.begin(), posts.end(), [&list_string](std::string &value) {
            std::string file_content = read_file(value);
            FileInfo *file_info = get_head(file_content);

            list_string +=
                    "<li><a href=\"posts/" + get_html_file_name(file_info) + "\">" + file_info->values["name"] +
                    "</a></li> \n";
        });

        index_content = replaceAll(index_content, "{{items}}", list_string);

        write_file("out/index.html", index_content);
    }

    std::cout << "Successfully generated the pages." << std::endl;

    return 0;
}