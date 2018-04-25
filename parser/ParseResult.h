#ifndef COMPILER_PARSERESULT_H
#define COMPILER_PARSERESULT_H

#include "CFGParser.h"

struct ParseResult {
    std::string msg;
    std::pair<Symbol, Production> rule;
    bool tokenDone;

    ParseResult() {
        msg = "";
    }
};


#endif //COMPILER_PARSERESULT_H
