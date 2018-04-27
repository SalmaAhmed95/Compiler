#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H

#include <vector>
#include <list>
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

    void parse(ParsingTable *parsingTable, Tokenizer *tokenizer, FileWriter *writer,
               FileWriter *leftDerivationWriter);

private:
    const Lexeme END_LEXEME = Lexeme(END, END);

    std::list<Symbol> *stack;
    ParsingTable *parseTable;
    std::list<Symbol> *derivativeLeftSide;

    Parser() {};

    Parser(Parser const &);

    void operator=(Parser const &);

    void initialize(ParsingTable *parseTable);

    ParseResult parse(Lexeme token);
};

#endif //COMPILER_PARSER_H
