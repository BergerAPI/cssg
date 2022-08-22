#include <string>
#include <filesystem>
#include <fstream>
#include <sys/stat.h>
#include "file.h"

std::string read_file(std::string path) {
    std::ifstream file(path);
    std::string result;

    std::string line;
    while (getline(file, line)) {
        result += line + "\n";
    }

    return result;
}

bool is_directory(const std::string &path) {
    const std::filesystem::path p(path);
    std::error_code e;

    return std::filesystem::is_directory(p, e);
}

bool directory_exists(std::string path)
{
    struct stat stats;

    stat(path.c_str(), &stats);

    if (S_ISDIR(stats.st_mode))
        return 1;

    return 0;
}

void create_directory(std::string path, bool remove_existing) {
    if (remove_existing && directory_exists(path))
        std::filesystem::remove_all(path);

    std::filesystem::create_directories(path);
}

std::vector<std::string> get_files_in_directory(std::string path) {
    std::vector<std::string> l;

    for (const auto &entry: std::filesystem::directory_iterator(path))
        l.push_back(entry.path());

    return l;
}

void write_file(std::string path, std::string content) {
    std::ofstream file(path);

    file << content;

    file.close();
}