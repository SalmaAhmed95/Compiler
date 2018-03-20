#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <vector>

enum TokenCharType { CHAR, OPERATOR, DEFAULT_TYPE };

struct RegexChar {
  char c;
  TokenCharType charType;
};

class Token {
public:
  Token();
  Token(std::string type, std::vector<RegexChar *> postfixRegex, int priority);
  virtual ~Token();
  int getPriority();
  std::vector<RegexChar *> getPostfixRegix();
  std::string getType();
  TokenCharType getCharType(int index);

private:
  std::string type;
  int priority;
  std::vector<RegexChar *> postfixRegex;
  int postFixRegexIter;
};

#endif
