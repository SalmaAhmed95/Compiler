//
// Created by salma on 16/03/18.
//

#include "../grammar-parser/Properties.hpp"
#include "CodeParser.h"

CodeParser::CodeParser(std::string fileName) { codeFile = fileName; }

std::vector<char> CodeParser::parseFile() {
  std::ifstream file(codeFile);
  std::string temp;
  char c;
  while (file.get(c)) { // loop getting single characters
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

void CodeParser::setStartIndex(int i) { index = i; }

int CodeParser::getCurIndex() { return index; }

std::string CodeParser::getSubString(int startIndex, int lastIndex) {
  std::string subString;
  for (int i = startIndex; i < lastIndex; i++) {
    subString += chars[i];
  }
  return subString;
}

bool CodeParser::hasChars() {
  if (index == chars.size() - 1)
    return false;
  return true;
}

bool CodeParser::isDelimeter(char c) { return iswspace(c); }

std::string CodeParser::getIdentifierClass(std::string propertiesFileName) {
  Properties::PropertiesData properties;
  std::ifstream propertiesFile(propertiesFileName.c_str());
  propertiesFile >> properties;
  if (properties.find(IDENTIFIER) != properties.end()) {
    return properties.find(IDENTIFIER)->second;
  }
  return IDENTIFIER;
}
