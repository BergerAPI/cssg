#pragma once

#include <iostream>
#include <vector>

std::string read_file(std::string path);

bool is_directory(const std::string &path);

std::vector<std::string> get_files_in_directory(std::string path);

void write_file(std::string path, std::string content);