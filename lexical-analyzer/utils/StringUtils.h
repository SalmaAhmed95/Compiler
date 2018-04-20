//
// Created by karfass on 18/04/2018.
//

#ifndef COMPILER_STRINGUTILS_H
#define COMPILER_STRINGUTILS_H


#include <string>

class StringUtils {

public:
    static std::size_t getFirstChar(std::string &line);
    static std::size_t getLastChar(std::string &line);
    static bool isDelimiter(char c);
    static std::vector<std::string> splitString( std::string &str, const std::string &delimiter);
    static std::string trimWhiteSpaces(std::string &str);

};


#endif //COMPILER_STRINGUTILS_H
