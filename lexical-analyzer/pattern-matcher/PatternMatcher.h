//
// Created by salma on 16/03/18.
//

#ifndef COMPILER_PATTERNMATCHER_H
#define COMPILER_PATTERNMATCHER_H

#include "../automata/DFA.h"
#include "../code-parser/CodeParser.h"
#include "../error/ErrorHandler.h"

class PatternMatcher {
public:
  PatternMatcher(DFA *dfa, std::string inputFile);

  bool findMatch(stateID startDFA, int startChar);

  void analyzeCode();

  void recoveryRoutine(int startIndex);

private:
  DFA *minDFA;
  CodeParser *parser;
  // to insert attribute value and corresponding type once match is found
  std::multimap<std::string, std::string> analysisTable;
};

#endif // COMPILER_PATTERNMATCHER_H
