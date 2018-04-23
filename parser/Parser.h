#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H

#include <vector>
#include <stack>
#include "CFGParser.h"
#include "ParsingTable.h"
#include "Grammar.h"


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


class Parser {
public:

    static Parser &getInstance() {
        static Parser parser;
        return parser;
    }

    void initialize(ParsingTable *parseTable);

    ParseResult parse(Symbol token);

    bool isDone();

private:

    Parser() {};

    Parser(Parser const &);

    void operator=(Parser const &);

    std::stack<Symbol> *stack;
    ParsingTable *parseTable;

    void printStack();
};

#endif //COMPILER_PARSER_H
