#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H

#include <vector>
#include <stack>
#include "CFGParser.h"
#include "ParsingTable.h"

class Parser {
public:

    static Parser &getInstance() {
        static Parser *parser;
        return *parser;
    }

    void initialize(ParsingTable *parseTable);

    std::pair<Production, std::string> *parse(Symbol *token);


private:
    Parser() {};

    Parser(Parser const &);

    void operator=(Parser const &);

    std::stack<Symbol> *stack;
    ParsingTable *parseTable;
};

#endif //COMPILER_PARSER_H
