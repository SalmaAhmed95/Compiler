#ifndef REGEX_TO_NFA_H
#define REGEX_TO_NFA_H
#include "../grammar-parser/Token.hpp"
#include "NFA.h"
#include <iostream>
#include <stack>

#define EPS_TRANS '`'
#define OR_OP '|'
#define CONC_OP '#'
#define STAR_OP '*'
#define PLUS_OP '+'

struct SubNfa {
  stateID startID;
  stateID endID;
};

class RegexToNfaConverter {
public:
  static NFA *getNfa(std::vector<Token *> tokens);

private:
  RegexToNfaConverter();
  static struct SubNfa *buildChar(char transition, NFA *nfa);
  static struct SubNfa *buildConcatenate(struct SubNfa *firstNfa,
                                         struct SubNfa *secondNfa, NFA *nfa);
  static struct SubNfa *buildOr(struct SubNfa *firstNfa,
                                struct SubNfa *secondNfa, NFA *nfa);
  static struct SubNfa *buildStar(struct SubNfa *subNfa, NFA *nfa);
  static struct SubNfa *buildPlus(struct SubNfa *subNfa, NFA *nfa);

  static struct SubNfa *createSubNfa(stateID startID, stateID endID);
  static struct SubNfa *convertToken(Token *token, NFA *nfa);
  static void doBinaryOperation(std::stack<struct SubNfa *> &nfaStack, NFA *nfa,
                                char operation);
  static void doUnaryOperation(std::stack<struct SubNfa *> &nfaStack, NFA *nfa,
                               char operation);
  static bool isBinaryOperation(char operation);
  static bool isUnaryOperation(char operation);
};

#endif
