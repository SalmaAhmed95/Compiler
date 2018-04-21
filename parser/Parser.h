#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H

#include <vector>
#include "CFGParser.h"
#include "ParseTable.h"

class Parser {
public:

    static Parser &getInstance() {
        static Parser parser; // Guaranteed to be destroyed. Instantiated on first use
        return instance;
    }

    static void initialize(ParseTable *parseTable);

    std::pair<Production, std::string> parse(Symbol* token);

    Parser(Parser const &) = delete;

    void operator=(Parser const &)  = delete;

private:
    Parser() {};
    std::stack<Symbol> *stack;
    ParseTable *parseTable;
};

#endif //COMPILER_PARSER_H
