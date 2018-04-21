//
// Created by karfass on 18/04/2018.
//
#include <vector>
#include <sstream>
#include <iostream>
#include "StringUtils.h"

std::size_t StringUtils::getFirstChar(std::string &line){
    std::size_t index = 0;
    while (!line.empty() && isDelimiter(line.at(index)) && index < line.length()){
        index++;
    }
    if (!line.empty() && index != line.length()) {
        return index;
    } else {
        return std::string::npos;
    }
};

std::size_t StringUtils::getLastChar(std::string &line){
    std::size_t index = line.length() - 1;
    while (isDelimiter(line.at(index))){
        index--;
    }
    return index;
};

bool StringUtils::isDelimiter(char c) { return iswspace(c); }

std::vector<std::string> StringUtils::splitString( std::string &str, const std::string &delimiter)
{
    std::vector<std::string> tokens;
    std::size_t prevfound = 0;
    std::size_t found = str.find(delimiter);
    while (found != std::string::npos) {
        std::string token = str.substr(prevfound, found - prevfound);
        prevfound = found + delimiter.length();
        found = str.find(delimiter, prevfound);
        tokens.push_back(token);
    }
    std::string token = str.substr(prevfound, str.length());
    tokens.push_back(token);
    return tokens;
}

std::string StringUtils::trimWhiteSpaces(std::string &str){
    size_t startIndex = getFirstChar(str);
    size_t endIndex = getLastChar(str);
    return str.substr(startIndex, endIndex + 1);
}