#ifndef TEST_HELPER_H
#define TEST_HELPER_H

#include "../grammar-parser/Production.hpp"
#include "../grammar-parser/Token.hpp"
#include <vector>

std::vector<Token *> buildTokens(std::vector<std::string> fakeTokens);

Token *buildToken(std::vector<std::string> fakeTokensType,
                  std::vector<std::string> fakeTokensRegex,
                  std::vector<int> fakeTokensPrecedence);

std::vector<RegexChar *> getRegexChars(std::string fakeTokenRegex);

bool isOperator(char c, TokenCharType charType);

#endif
