//
// Created by salma on 16/03/18.
//

#include <vector>
#include <fstream>
#include <iostream>
#include "CodeParser.h"

CodeParser::CodeParser(std::string fileName) {
    codeFile = fileName;
}

std::vector<char> CodeParser::parseFile() {
    std::ifstream file(codeFile);
    std::string temp;
    char c;
    while (file.get(c)) {      // loop getting single characters
        chars.push_back(c);
    }
    file.close();
    return chars;
}

char CodeParser::getChar() {
    char c = chars[index];
    index++;
    return c;
}

void CodeParser::setStartIndex(int i) {
    index = i;
}

int CodeParser::getCurIndex() {
    return index;
}

std::string CodeParser::getSubString(int startIndex,int lastIndex) {
    std::string subString;
    for (int i = startIndex; i < lastIndex; i++) {
        subString += chars[i];
    }
    return subString;
}

bool CodeParser::hasChars() {
    if (index == chars.size() +1)
        return false;
    return true;
}
bool CodeParser::isDelimeter(char c) {
    if(c == SPACE || c == NEWLINE)
        return true;
    return false;
}