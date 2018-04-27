//
// Created by salma on 16/03/18.
//

#include "SymbolTable.h"

std::set<std::string> SymbolTable::table;

void SymbolTable::insert(std::string identifierVal) {
    table.insert(identifierVal);
}

std::set<std::string> SymbolTable::getAllIndetifiers() {

}

bool SymbolTable::contains(std::string id) {
    return table.find(id) != table.end();
}