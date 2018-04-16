//
// Created by salma on 16/03/18.
//

#ifndef COMPILER_PATTERNMATCHER_H
#define COMPILER_PATTERNMATCHER_H

#include "../automata/DFA.h"
#include "../code-parser/CodeParser.h"
#include "../error/ErrorHandler.h"
#include "../file-writer/FileWriter.h"
#include "../utils/SymbolTable.h"

class PatternMatcher {
public:
    PatternMatcher(DFA *dfa, std::string inputFile,std::string properties, FileWriter *writer);

    bool findMatch(stateID startDFA, int startChar);

    std::vector<std::string> analyzeCode();

    void recoveryRoutine(int startIndex);
    
    

private:
    DFA *minDFA;
    CodeParser *parser;
    FileWriter *fwriter;
    std::string propertiesFile;
    SymbolTable *symbolTable;

    // to insert tokens in order
    std::vector<std::string> analysisTable;
};

#endif // COMPILER_PATTERNMATCHER_H
