#include "Token.hpp"

Token::Token() : type(""), postfixRegex(""), priority((int)0) {}

Token::Token(std::string type, std::string postfixRegex, int priority)
    : type(type), postfixRegex(postfixRegex), priority((int)priority) {}

int Token::getPriority() { return priority; }

std::string Token::getType() { return type; }

std::string Token::getPostfixRegix() { return postfixRegex; }

void Token::setPriority(int priority) { this->priority = priority; }

void Token::setPostfixRegex(std::string postfixRegex) {
  this->postfixRegex = postfixRegex;
}

void Token::setType(std::string type) { this->type = type; }

Token::~Token() {}
