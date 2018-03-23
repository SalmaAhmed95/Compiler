#ifndef REGEX_TO_NFA_H
#define REGEX_TO_NFA_H
#include "../grammar-parser/Token.hpp"
#include "Definitions.h"
#include "NFA.h"
#include <algorithm>
#include <iostream>
#include <limits.h>
#include <stack>
#include <utility>

// #define EPS_TRANS '`'
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
  static struct SubNfa *buildChar(char transition, NFA *nfa,
                                  std::vector<stateID> &createdNodes);
  static struct SubNfa *buildConcatenate(struct SubNfa *firstNfa,
                                         struct SubNfa *secondNfa, NFA *nfa);
  static struct SubNfa *buildOr(struct SubNfa *firstNfa,
                                struct SubNfa *secondNfa, NFA *nfa,
                                std::vector<stateID> &createdNodes);
  static struct SubNfa *buildStar(struct SubNfa *subNfa, NFA *nfa,
                                  std::vector<stateID> &createdNodes);
  static struct SubNfa *buildPlus(struct SubNfa *subNfa, NFA *nfa,
                                  std::vector<stateID> &createdNodes);

  static struct SubNfa *createSubNfa(stateID startID, stateID endID);
  static struct SubNfa *convertToken(Token *token, NFA *nfa);
  static void doBinaryOperation(std::stack<struct SubNfa *> &nfaStack, NFA *nfa,
                                char operation,
                                std::vector<stateID> &createdNodes);
  static void doUnaryOperation(std::stack<struct SubNfa *> &nfaStack, NFA *nfa,
                               char operation,
                               std::vector<stateID> &createdNodes);
  static bool isBinaryOperation(RegexChar *regexChar);
  static bool isUnaryOperation(RegexChar *regexChar);
  static StateType getState(bool isLast);
  static bool validatePostfix(Token *token);
  static std::pair<int, int> getAsciiRange(std::vector<Token *> tokens);
};

#endif
