//
// Created by salma on 16/03/18.
//

#ifndef COMPILER_SYMBOLTABLE_H
#define COMPILER_SYMBOLTABLE_H

#include <string>
#include <vector>

class SymbolTable {
public:
    SymbolTable();

    void insert(std::string identifierVal);

    std::vector<std::string> getAllIndetifiers();

protected:
    std::vector<std::string> *table;
};


#endif //COMPILER_SYMBOLTABLE_H
