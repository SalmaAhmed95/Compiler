//
// Created by salma on 19/04/18.
//

#include "ParserTable.h"

Production ParserTable::getProduction(ParsingTable &parserTable, Symbol nonTerminal, Symbol terminal) {
   return parserTable.table[nonTerminal][terminal];
}

void ParserTable::insertProduction(ParsingTable &parserTable, Symbol nonTerminal, Symbol terminal, Production production) {
    std::map<Symbol, Production> inner;
    inner.insert(std::make_pair(terminal, production));
    parserTable.table.insert(std::make_pair(nonTerminal, inner));
}