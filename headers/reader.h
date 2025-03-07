#ifndef PROGAMING_LANGUAGE_READER_H
#define PROGAMING_LANGUAGE_READER_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "string_utils.h"

bool is_whitespace(const std::string& s) {
    return std::all_of(s.begin(), s.end(), isspace);
}


std::vector<std::string> read_file(const std::string &fileName) {
    std::vector<std::string> lines;
    std::ifstream file(fileName);

    // Check if the file opened successfully
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return lines;
    }

    std::string line;
    while (std::getline(file, line))
        if (!isEmpty(line) && !isSpace(line))
            lines.push_back(rstrip(line));

    file.close();
    return lines;
}

#endif
