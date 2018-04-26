//
// Created by salma on 16/03/18.
//

#ifndef COMPILER_Tokenizer_H
#define COMPILER_Tokenizer_H

#include "../automata/DFA.h"
#include "../code-parser/CodeParser.h"
#include "../error/ErrorHandler.h"
#include "../file-writer/FileWriter.h"
#include "../utils/SymbolTable.h"

#define EMPTYSTRING ""

class Tokenizer {
public:
    Tokenizer(DFA *dfa, std::string inputFile, std::string properties, FileWriter *writer);

    bool findMatch(stateID startDFA, int startChar);

    std::string nextToken();

    bool hasTokens();

    bool tokenFound();

    void recoveryRoutine(int startIndex);


private:
    DFA *minDFA;
    CodeParser *parser;
    FileWriter *fwriter;
    std::string propertiesFile;
    SymbolTable *symbolTable;
    std::string token;
};

#endif // COMPILER_Tokenizer_H
