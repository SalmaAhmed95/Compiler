//
// Created by salma on 16/03/18.
//

#include <vector>
#include <fstream>
#include "CodeParser.h"

CodeParser::CodeParser(std::string fileName) {
    codeFile = fileName;
}

std::vector<char> CodeParser::parseFile() {
    std::ifstream file(codeFile);
    std::string temp;
    char c;
    while (file.get(c))       // loop getting single characters
        chars.push_back(c);

    file.close();
    return chars;
}

char CodeParser::getChar() {
    return chars[index];
}

void CodeParser::setStartIndex(int i) {
    index = i;
}

bool CodeParser::hasChars() {
    if (index == chars.size() - 1)
        return false;
    return true;
}