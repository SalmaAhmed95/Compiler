//
// Created by salma on 16/03/18.
//

#ifndef COMPILER_SYMBOLTABLE_H
#define COMPILER_SYMBOLTABLE_H

#include <string>
#include <set>

class SymbolTable {
public:
    static void insert(std::string identifierVal);

    static bool contains(std::string id);

    static std::set<std::string> getAllIndetifiers();

protected:
    static std::set<std::string> table;
};


#endif //COMPILER_SYMBOLTABLE_H
