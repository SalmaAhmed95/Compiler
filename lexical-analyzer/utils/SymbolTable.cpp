//
// Created by salma on 16/03/18.
//

#include "SymbolTable.h"

SymbolTable::SymbolTable() {
    table=new std::vector<std::string>;
}

void SymbolTable::insert(std::string identifierVal) {
   table->push_back(identifierVal);
}

std::vector<std::string> SymbolTable::getAllIndetifiers() {

}