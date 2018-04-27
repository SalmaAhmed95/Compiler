//
// Created by salma on 16/03/18.
//

#ifndef COMPILER_Tokenizer_H
#define COMPILER_Tokenizer_H

#include "../automata/DFA.h"
#include "../code-parser/CodeParser.h"
#include "../../file-writer/FileWriter.h"
#include "../../error/ErrorHandler.h"
#include "../../utils/SymbolTable.h"

struct Lexeme {
    std::string name;
    std::string lexemeType;

    Lexeme() {}

    Lexeme(std::string, std::string lexemeType) {
        this->name = name;
        this->lexemeType = lexemeType;
    }

    bool operator==(const Lexeme &lexeme) const {
        return name == lexeme.name && lexemeType == lexeme.lexemeType;
    }
};

class Tokenizer {
public:

    Tokenizer(DFA *dfa, std::string inputFile, std::string properties, FileWriter *writer);

    bool findMatch(stateID startDFA, int startChar);

    struct Lexeme nextToken();

    bool hasTokens();

    bool tokenFound();

    void recoveryRoutine(int startIndex);


private:
    DFA *minDFA;
    CodeParser *parser;
    FileWriter *fwriter;
    std::string propertiesFile;
    SymbolTable *symbolTable;
    struct Lexeme token;
};

#endif // COMPILER_Tokenizer_H
