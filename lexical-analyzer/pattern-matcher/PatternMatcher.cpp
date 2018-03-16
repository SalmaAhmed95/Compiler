//
// Created by salma on 16/03/18.
//

#include "PatternMatcher.h"

PatternMatcher::PatternMatcher(DFA *dfa, std::string inputFile) {
    minDFA = dfa;
    parser = new CodeParser(inputFile);
    parser->parseFile();
}

void PatternMatcher::analyzeCode() {
    stateID start = minDFA->getRootID();
    while (parser->hasChars()) {
       if(!findMatch(start)){
           recoveryRoutine();
           // then try to continue finding patterns (handle later)
       }
    }
}
bool PatternMatcher::findMatch(stateID start) {
   stateID curState = start;
   while(parser->getChar()!= SPACE /* && curState != PHI state*/){

   }

}

void PatternMatcher::recoveryRoutine() {

}