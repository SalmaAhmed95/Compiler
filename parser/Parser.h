#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H

#include <vector>
#include <stack>
#include "CFGParser.h"
#include "ParsingTable.h"
#include "Grammar.h"
#include "ParseResult.h"
#include "../lexical-analyzer/tokenizer/Tokenizer.h"

class Parser {
public:

    static Parser &getInstance() {
        static Parser parser;
        return parser;
    }

    void parse(ParsingTable *parsingTable, Tokenizer *tokenizer, FileWriter *writer);

private:
    const Lexeme END_LEXEME = Lexeme(END, END);

    Parser() {};

    Parser(Parser const &);

    void operator=(Parser const &);

    void initialize(ParsingTable *parseTable);

    ParseResult parse(Lexeme token);

    std::stack<Symbol> *stack;
    ParsingTable *parseTable;

    void printStack();
};

#endif //COMPILER_PARSER_H
