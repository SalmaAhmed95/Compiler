#ifndef COMPILER_PARSERESULT_H
#define COMPILER_PARSERESULT_H

#include "CFGParser.h"

struct ParseResult {
    std::string msg;
    std::pair<Symbol, Production> rule;
    bool tokenDone;

    ParseResult() {
        tokenDone = false;
        msg = "";
    }

    ParseResult(bool tokenMatched) {
        this->tokenDone = tokenMatched;
        msg = "";
    }

};


#endif //COMPILER_PARSERESULT_H
