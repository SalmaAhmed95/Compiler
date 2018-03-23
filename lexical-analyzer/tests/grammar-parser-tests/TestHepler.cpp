#include "TestHelper.hpp"

std::vector<Token *> buildTokens(std::vector<std::string> fakeTokensType,
                                 std::vector<std::string> fakeTokensRegex,
                                 std::vector<int> fakeTokensPrecedence) {
  std::vector<Token *> realTokens;
  if (fakeTokensRegex.size() != fakeTokensPrecedence.size() ||
      fakeTokensRegex.size() != fakeTokensType.size()) {
    return realTokens;
  }
  for (int i = 0; i < (int)fakeTokensType.size(); i++) {
    realTokens.push_back(buildToken(fakeTokensType[i], fakeTokensRegex[i],
                                    fakeTokensPrecedence[i]));
  }
  return realTokens;
}

Token *buildToken(std::string tokenType, std::string fakeTokenStr,
                  int tokenPrecendence) {
  return new Token(tokenType, getRegexChars(fakeTokenStr), tokenPrecendence);
}

std::vector<RegexChar *> getRegexChars(std::string fakeTokenRegex) {
  std::vector<RegexChar *> regexChars;
  for (int i = 0; i < (int)fakeTokenRegex.size(); i++) {
    TokenCharType charType = fakeTokenRegex[i] == '\\' ? CHAR : OPERATOR;
    i += charType == CHAR;
    charType = isOperator(fakeTokenRegex[i], charType) ? OPERATOR : CHAR;
    regexChars.push_back(
        ProductionParser::makeRegexChar(fakeTokenRegex[i], charType));
  }
  return regexChars;
}

bool isOperator(char c, TokenCharType charType) {
  return charType != CHAR &&
         (c == ProductionParser::OR || c == ProductionParser::CONCATENATE ||
          c == ProductionParser::STAR || c == ProductionParser::PLUS);
}

std::string getRange(char startC, char endC) {
  std::string range = "";
  for (char i = startC; i <= endC; i++) {
    range = range + i + (i != endC ? "|" : "");
  }
  return range;
}
