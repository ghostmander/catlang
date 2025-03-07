#ifndef CATLANG_READER_H
#define CATLANG_READER_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "string_utils.h"

/**
 * File reading utility function.
 * This function raises an error if the file cannot be opened. It also strips the end of each line, while filtering out empty lines.
 * @param fileName The path of the file to read.
 * @return A vector of strings, each representing a line from the file.
 */
inline std::vector<std::string> read_file(const std::string &fileName) {

    std::vector<std::string> lines;
    std::ifstream file(fileName);

    // Check if the file opened successfully
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << fileName << std::endl;
        exit(-1);
    }

    std::string line;
    while (std::getline(file, line))
        if (!isEmpty(line) && !isSpace(line)) /// Filter out empty lines
            lines.push_back(rstrip(line)); /// Trim out spaces at the end of the line

    file.close();
    return lines;
}

#endif
