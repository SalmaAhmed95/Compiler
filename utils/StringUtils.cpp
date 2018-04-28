//
// Created by karfass on 18/04/2018.
//
#include <vector>
#include <sstream>
#include <iostream>
#include "StringUtils.h"

int StringUtils::getFirstChar(std::string &line){
    int index = -1;
    if (!line.empty()){
        index = 0;
    }
   while (!line.empty() && index < line.length() && isDelimiter(line.at(index)) ){
        index++;
    }
    return index;
};

int StringUtils::getLastChar(std::string &line){
    int index = line.length() - 1;
    while (index >= 0 && isDelimiter(line.at(index))){
        index--;
    }
    return index;
};

bool StringUtils::isDelimiter(char c) { return iswspace(c); }

std::vector<std::string> StringUtils::splitString( std::string &str, const std::string &delimiter)
{

    std::vector<std::string> tokens;
    std::size_t prevfound = 0, prevFound2 = 0;
    std::size_t found = str.find(delimiter);
    while (found != std::string::npos) {
        if (found == 0 || (found > 0 && str.at(found - 1) != '\\')) {
        std::string token = str.substr(prevfound, found - prevfound);
        prevfound = found + delimiter.length();
        token = trimWhiteSpaces(token);
        if (!token.empty())
            tokens.push_back(token);
        }
        prevFound2 = found + delimiter.length();
        found = str.find(delimiter, prevFound2);
    }
    std::string token = str.substr(prevfound, str.length());
    token = trimWhiteSpaces(token);
    if (!token.empty())
        tokens.push_back(token);
    return tokens;
}

std::string StringUtils::trimWhiteSpaces(std::string &str){
    int startIndex = getFirstChar(str);
    int endIndex = getLastChar(str);
    if (endIndex == -1){
        return "";
    }
    return str.substr(startIndex,  endIndex - startIndex + 1);
}

bool StringUtils::isAlphabet(char c){
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
        return true;
    }
    return false;
}

bool StringUtils::isAlphaNumeric(char c) {
    if (isAlphabet(c) || (c >='0' && c<='9') || (c == '_')) {
        return true;
    }
    return false;
}