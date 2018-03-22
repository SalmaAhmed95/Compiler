//
// Created by salma on 16/03/18.
//

#ifndef COMPILER_CODEPARSER_H
#define COMPILER_CODEPARSER_H

#include <vector>
#include <string>

#define IDENTIFIER "identifier"

class CodeParser {

public:
  explicit CodeParser(std::string fileName);

  std::vector<char> parseFile();

  char getChar();

  void setStartIndex(int i);

  int getCurIndex();

  std::string getSubString(int startIndex, int lastIndex);

  bool hasChars();

  bool isDelimeter(char c);

    std::string getIdentifierClass(std::string propertiesFileName);

private:
  std::string codeFile;
  int index = 0;
  std::vector<char> chars;
};

#endif // COMPILER_CODEPARSER_H
