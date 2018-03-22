#ifndef TEST_HELPER_H
#define TEST_HELPER_H

#include "../../grammar-parser/ProductionParser.hpp"
#include "../../grammar-parser/Token.hpp"
#include <vector>

std::vector<Token *> buildTokens(std::vector<std::string> fakeTokensType,
                                 std::vector<std::string> fakeTokensRegex,
                                 std::vector<int> fakeTokensPrecedence);

Token *buildToken(std::string tokenType, std::string fakeTokenStr,
                  int tokenPrecendence);

std::string getRange(char startC, char endC);

std::vector<RegexChar *> getRegexChars(std::string fakeTokenRegex);

bool isOperator(char c, TokenCharType charType);

#endif
