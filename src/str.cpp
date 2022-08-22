#include <iostream>
#include "str.h"

std::string str_trim(std::basic_string<char> str) {
    str.erase(str.find_last_not_of(' ') + 1);
    str.erase(0, str.find_first_not_of(' '));

    return str;
}

bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);

    if(start_pos == std::string::npos)
        return false;

    str.replace(start_pos, from.length(), to);
    return true;
}

std::string replaceAll(std::string str, const std::string& from, const std::string& to) {
    if(from.empty())
        return str;

    size_t start_pos = 0;

    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }

    return str;
}
