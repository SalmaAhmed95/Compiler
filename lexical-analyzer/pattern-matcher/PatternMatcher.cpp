// //
// // Created by salma on 16/03/18.
// //

#include "PatternMatcher.h"
#include "../file-writer/FileWriter.h"

PatternMatcher::PatternMatcher(DFA *dfa, std::string inputFile,std::string properties , FileWriter *writer) {
    minDFA = dfa;
    parser = new CodeParser(inputFile);
    parser->parseFile();
    propertiesFile=properties;
    fwriter = writer;
    symbolTable = new SymbolTable();
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
    std::string tokenType;
    int matchIndex = -1;
    int prevPercedence = INT16_MIN;
    char c = parser->getChar();
    std::set<char> attr = minDFA->getAllAttributes();
    std::set<char>::iterator it = attr.find(c);
    while (parser->hasChars() && !parser->isDelimeter(c) && !minDFA->isPHI(curState) && it != attr.end() ) {
        nextState = minDFA->getTransitions(curState, c);
        if (minDFA->isAccepted(nextState[0]) && minDFA->getPrecedence(curState) >= prevPercedence) {
            matchIndex = parser->getCurIndex();
            match = parser->getSubString(startChar, matchIndex);
            tokenType = minDFA->getTokenClass(nextState[0]);
            prevPercedence = minDFA->getPrecedence(curState);
        }
        curState = nextState[0];
        c = parser->getChar();
        it = attr.find(c);
    }
    if(parser->isDelimeter(c) && matchIndex == -1)
        return true;
    else if (matchIndex == -1) {
        return false;
    } else {
        parser->setStartIndex(matchIndex);
        analysisTable.insert(std::pair<std::string, std::string>(match, tokenType));
        fwriter->writeMatch(match,tokenType);
        std::string tokenType = minDFA->getTokenClass(curState);
        analysisTable.insert(std::pair<std::string, std::string>(match, tokenType));
        if(tokenType == parser->getIdentifierClass(propertiesFile));
            symbolTable->insert(match);

        return true;
    }
}

void PatternMatcher::recoveryRoutine(int startIndex) {
    /*drop one letter from stream in order to start matching again from after
    that
     * letter*/
    parser->setStartIndex(startIndex);
    // print message from error handler
    fwriter->writeError(ErrorHandler::errors[ErrorHandler::lexicalError]);

}
