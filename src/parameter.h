#pragma once

#include <iostream>
#include <map>
#include <vector>

/* Information about a parameter that could be passed to the command line */
struct Parameter {
    std::string name = {};
    bool required = {};
};

/* All command line parameter that are available to use  */
const std::vector<Parameter> available_parameter = {
        Parameter{"input", true},
        Parameter{"post-template", true},
        Parameter{"index-template", false},
};

std::map<std::string, std::string> parse_argv(char **argv);