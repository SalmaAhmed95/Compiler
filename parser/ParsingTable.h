//
// Created by salma on 19/04/18.
//

#ifndef COMPILER_PARSETABLE_H
#define COMPILER_PARSETABLE_H

#include "CFGParser.h"


#include <map>

#define SYNC "sync"

class ParsingTable {

public:

    Production getProduction(Symbol nonTerminal, Symbol terminal);

    bool isEmpty(Symbol nonTerminal, Symbol terminal);

    bool isSync(Symbol nonTerminal, Symbol terminal);

    Symbol getStartSymbol();

    std::map<Symbol, std::map<Symbol, Production>> getTable();

private:
    std::map<Symbol, std::map<Symbol, Production>> parsingTable;

    void insertProduction(Symbol nonTerminal, Symbol terminal, Production production);

    void setStartSymbol(Symbol start);

    Symbol start;

    friend class Grammar;
};


#endif //COMPILER_PARSETABLE_H
