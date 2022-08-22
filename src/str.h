#pragma once

std::string str_trim(std::basic_string<char> str);

bool replace(std::string& str, const std::string& from, const std::string& to);

std::string replaceAll(std::string str, const std::string& from, const std::string& to);