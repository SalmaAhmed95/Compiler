//
// Created by salma on 19/04/18.
//

#include "ParsingTable.h"

Production ParsingTable::getProduction(Symbol nonTerminal, Symbol terminal) {
   return parsingTable[nonTerminal][terminal];
}

void ParsingTable::insertProduction(Symbol nonTerminal, Symbol terminal, Production production) {
    std::map<Symbol, Production> inner;
    inner.insert(std::make_pair(terminal, production));
    parsingTable.insert(std::make_pair(nonTerminal, inner));
}


bool ParsingTable::isEmpty(Symbol *pSymbol, Symbol *pSymbol1) {
    //TODO implement this function. It is needed in the Parse Algorithm
    return false;
}

bool ParsingTable::isSync(Symbol *pSymbol, Symbol *pSymbol1) {
    //TODO implement this function. It is needed in the Parse Algorithm
    return false;
}
