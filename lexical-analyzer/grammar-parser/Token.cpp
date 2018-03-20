#include "Token.hpp"

Token::Token() : type(""), priority((int)0) {}

Token::Token(std::string type, std::vector<RegexChar *> postfixRegex,
             int priority)
    : type(type), postfixRegex(postfixRegex), priority((int)priority) {}

int Token::getPriority() { return priority; }

std::string Token::getType() { return type; }

std::vector<RegexChar *> Token::getPostfixRegix() { return postfixRegex; }

Token::~Token() {}
