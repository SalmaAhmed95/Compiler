//
// Created by salma on 19/04/18.
//

#ifndef COMPILER_PARSETABLE_H
#define COMPILER_PARSETABLE_H

#include "CFGParser.h"


#include <map>

class ParsingTable {

public:

    Production getProduction(Symbol nonTerminal, Symbol terminal);

    bool isEmpty(Symbol *pSymbol, Symbol *pSymbol1);

    bool isSync(Symbol *pSymbol, Symbol *pSymbol1);

private:
    std::map<Symbol, std::map<Symbol, Production>> parsingTable;
    void insertProduction(Symbol nonTerminal,Symbol terminal, Production production );

    friend class Grammar;
};


#endif //COMPILER_PARSETABLE_H
