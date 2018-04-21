//
// Created by salma on 19/04/18.
//

#ifndef COMPILER_PARSETABLE_H
#define COMPILER_PARSETABLE_H

#include "CFGParser.h"


#include <map>

class ParserTable {

public:

    static Production getProduction(ParsingTable &table,Symbol nonTerminal, Symbol terminal);

    static void insertProduction(ParsingTable &table,Symbol nonTerminal,Symbol terminal, Production production );


};


#endif //COMPILER_PARSETABLE_H
