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