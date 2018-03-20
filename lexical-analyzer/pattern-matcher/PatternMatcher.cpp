// //
// // Created by salma on 16/03/18.
// //

#include "PatternMatcher.h"

PatternMatcher::PatternMatcher(DFA *dfa, std::string inputFile) {
  minDFA = dfa;
  parser = new CodeParser(inputFile);
  parser->parseFile();
}

void PatternMatcher::analyzeCode() {
  stateID startDFA = minDFA->getRootID();
  while (parser->hasChars()) {
    int curIndex = parser->getCurIndex();
    if (!findMatch(startDFA, curIndex)) {
      // if match not found print error then advance ptr & try to continue
      // finding patterns
      recoveryRoutine(curIndex + 1);
    }
  }
}

bool PatternMatcher::findMatch(stateID startDFA, int startChar) {
  stateID curState = startDFA;
  std::vector<stateID> nextState;
  std::string match;
  int matchIndex = -1;
  int prevPercedence = INT16_MIN;
  char c = parser->getChar();
  while (parser->hasChars() && !parser->isDelimeter(c) &&
         !minDFA->isPHI(curState)) {
    nextState = minDFA->getTransitions(curState, c);
    // std::cout<<curState<<" "<<c<<std::endl;
    if (minDFA->isAccepted(nextState[0]) &&
        minDFA->getPrecedence(curState) >= prevPercedence) {
      matchIndex = parser->getCurIndex();
      match = parser->getSubString(startChar, matchIndex);
      prevPercedence = minDFA->getPrecedence(curState);
      // std::cout << "match: " << match << std::endl;
    }

    curState = nextState[0];
    c = parser->getChar();
  }
  if (matchIndex == -1) {
    return false;
  } else {
    std::cout << "match: " << match << matchIndex << std::endl;
    parser->setStartIndex(matchIndex);

    std::string tokenType = minDFA->getTokenClass(curState);
    analysisTable.insert(std::pair<std::string, std::string>(match, tokenType));
    // if(tokenType == IDENTIFIER) insert into symbol table for next phase

    return true;
  }
}

void PatternMatcher::recoveryRoutine(int startIndex) {
  /*drop one letter from stream in order to start matching again from after
  that
   * letter*/
  parser->setStartIndex(startIndex);
  // print message from error handler
  // send this error message to a writer to write it
  // ErrorHandler::lexicalError;
}
