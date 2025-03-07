#include <iostream>
#include "reader.h"
#include "string_utils.h"

int main(int argc, char *argv[]) {
    std::cout << "Hello World" << std::endl;

    std::cout << argc << std::endl;
//    for (const auto& arg: argv)
//        std::cout << arg << ", ";
    std::vector<std::string> lines = read_file("../test.nya");
    // Print the lines to verify
    for (const auto& line : lines) {
        std::cout << line << '[';
        for (const auto& token: split(line))
            std::cout << "'" << token << "'";
        std::cout << ']' << std::endl;
    }

    return 0;
}
