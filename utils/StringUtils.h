//
// Created by karfass on 18/04/2018.
//

#ifndef COMPILER_STRINGUTILS_H
#define COMPILER_STRINGUTILS_H


#include <string>

class StringUtils {

public:
    static int getFirstChar(std::string &line);
    static int getLastChar(std::string &line);
    static bool isDelimiter(char c);
    static bool isAlphabet(char c);
    static bool isAlphaNumeric(char c);
    static std::vector<std::string> splitString( std::string &str, const std::string &delimiter);
    static std::string trimWhiteSpaces(std::string &str);

};


#endif //COMPILER_STRINGUTILS_H
