//
// Created by salma on 19/04/18.
//

#include "ParsingTable.h"

Production ParsingTable::getProduction(Symbol nonTerminal, Symbol terminal) {
    return parsingTable[nonTerminal][terminal];
}

void ParsingTable::insertProduction(Symbol nonTerminal, Symbol terminal, Production production) {
    parsingTable[nonTerminal].insert(std::make_pair(terminal, production));
}

bool ParsingTable::isEmpty(Symbol nonTerminal, Symbol terminal) {
    auto it = parsingTable[nonTerminal].find(terminal);
    return (it == parsingTable[nonTerminal].end());
}

bool ParsingTable::isSync(Symbol nonTerminal, Symbol terminal) {
    Production prod = parsingTable[nonTerminal][terminal];
    return prod.production[0].name == SYNC;
}


Symbol ParsingTable::getStartSymbol() {
    return start;
}

void ParsingTable::setStartSymbol(Symbol start) {
    this->start = start;
}

std::map<Symbol, std::map<Symbol, Production>> ParsingTable::getTable() {
    return parsingTable;
}

