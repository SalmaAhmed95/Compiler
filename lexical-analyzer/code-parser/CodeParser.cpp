//
// Created by salma on 16/03/18.
//

#include <vector>
#include <fstream>
#include "CodeParser.h"

CodeParser::CodeParser() {}

std::vector<char> CodeParser::getChars(std::string fileName) {
    std::ifstream file(fileName);
    std::string temp;
    std::vector<char> chars;
    char c;
    while (file.get(c))       // loop getting single characters
        chars.push_back(c);

    file.close();
    return chars;
}