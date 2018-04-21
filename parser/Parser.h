#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H

#include <vector>
#include <stack>
#include "CFGParser.h"
#include "ParserTable.h"

class Parser {
public:

    static Parser &getInstance() {
        static Parser parser; // Guaranteed to be destroyed. Instantiated on first use
        return parser;
    }

    static void initialize(ParserTable *parseTable);

    std::pair<Production, std::string> parse(Symbol* token);

    Parser(Parser const &) = delete;

    void operator=(Parser const &)  = delete;

private:
    Parser() {};
    std::stack<Symbol> *stack;
    ParserTable *parseTable;
};

#endif //COMPILER_PARSER_H
