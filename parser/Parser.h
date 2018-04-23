#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H

#include <vector>
#include <stack>
#include "CFGParser.h"
#include "ParsingTable.h"
#include "Grammar.h"

class Parser {
public:

    static Parser &getInstance() {
        static Parser *parser;
        return *parser;
    }

    void initialize(ParsingTable parseTable);

    std::pair<std::pair<Symbol, Production>, std::string> parse(Symbol token);

    bool wasSuccessful();

private:
    Parser() {};

    Parser(Parser const &);

    void operator=(Parser const &);

    std::stack<Symbol> *stack;
    ParsingTable parseTable;
};

#endif //COMPILER_PARSER_H
