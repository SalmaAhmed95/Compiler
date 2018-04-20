// //
// // Created by salma on 16/03/18.
// //

#include "../file-writer/FileWriter.h"
#include "Tokenizer.h"

Tokenizer::Tokenizer(DFA *dfa, std::string inputFile,
                     std::string properties, FileWriter *writer) {
    minDFA = dfa;
    parser = new CodeParser(inputFile);
    parser->parseFile();
    propertiesFile = properties;
    fwriter = writer;
    symbolTable = new SymbolTable();
}
std::string Tokenizer::nextToken() {
    stateID startDFA = minDFA->getRootID();
        int curIndex = parser->getCurIndex();
        if (!findMatch(startDFA, curIndex)) {
            // if match not found print error then advance ptr & try to continue
            // finding patterns
            recoveryRoutine(curIndex + 1);
        }
    return token;
}

bool Tokenizer::findMatch(stateID startDFA, int startChar) {
    stateID curState = startDFA;
    std::vector<stateID> nextState;
    std::string match;
    std::string tokenType;
    int matchIndex = -1;
    token ="";
    int prevPercedence = INT16_MIN;
    char c;
    std::set<char> attr = minDFA->getAllAttributes();
    std::set<char>::iterator it;
    while (parser->hasChars()) {

        c = parser->getChar();
        it = attr.find(c);
        if (parser->isDelimeter(c) || minDFA->isPHI(curState) || it == attr.end())
            break;
        nextState = minDFA->getTransitions(curState, c);
        if (minDFA->isAccepted(nextState[0])) {
            matchIndex = parser->getCurIndex();
            match = parser->getSubString(startChar, matchIndex);
            tokenType = minDFA->getTokenClass(nextState[0]);
            prevPercedence = minDFA->getPrecedence(nextState[0]);
        }
        curState = nextState[0];
    }

    if (parser->isDelimeter(c) && matchIndex == -1) {
        return true;
    } else if (matchIndex == -1) {
        return false;
    } else {
        parser->setStartIndex(matchIndex);
        fwriter->writeMatch(match, tokenType);
        if (tokenType == parser->getIdentifierClass(propertiesFile))
            symbolTable->insert(match);
        token = match;
        return true;
    }
}
bool Tokenizer::hasTokens() {
    parser->hasChars();
}

bool Tokenizer::tokenFound() {
    if(token!="")
        return true;
    else false;
}
void Tokenizer::recoveryRoutine(int startIndex) {
    /*drop one letter from stream in order to start matching again from after
    that
     * letter*/
    parser->setStartIndex(startIndex);
    // print message from error handler
    fwriter->writeError(ErrorHandler::errors[ErrorHandler::lexicalError]);
}
