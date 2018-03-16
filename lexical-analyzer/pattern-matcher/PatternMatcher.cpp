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
    stateID startDFA = minDFA->getRootID();
    while (parser->hasChars()) {
        if (!findMatch(startDFA, parser->getCurIndex())) {
            recoveryRoutine();
            // then try to continue finding patterns (handle later)
        }
    }
}

bool PatternMatcher::findMatch(stateID startDFA, int startChar) {
    stateID curState = startDFA;
    std::vector<stateID> nextState;
    std::string match = "";
    int matchIndex = -1;
    int prevPercedence = INT16_MIN;
    char c = parser->getChar();
    while (c != SPACE /* && curState != PHI state*/) {
        nextState = minDFA->getTransitions(curState, c);
        if (nextState[0].isAcceptance && minDFA->getAcceptance(curState)->precedence > prevPercedence) {
            matchIndex = parser->getCurIndex();
            match = parser->getSubString(startChar, matchIndex);
            prevPercedence = minDFA->getAcceptance(curState)->precedence;
        }

        curState = nextState[0];
        c = parser->getChar();
    }
    if (c == SPACE)
        parser->setStartIndex(parser->getCurIndex() + 1);
    if (matchIndex == -1) {
        return false;
    } else {
        parser->setStartIndex(matchIndex + 1);
        std::string tokenType = minDFA->getAcceptance(curState)->type;
        analysisTable.insert(match, tokenType);
        //if(tokenType == IDENTIFIER) insert into symbol table for next phase

        return true;
    }

}

void PatternMatcher::recoveryRoutine() {

}