

#ifndef COMPILER_CFGPARSER_H
#define COMPILER_CFGPARSER_H

#include <map>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include "../lexical-analyzer/grammar-parser/Properties.hpp"

#define EPSILONSYMBOl "\\L"

enum SymbolType {
    TERMINAL, NON_TERMINAL, START, EPSILON
};

struct Symbol {
    std::string name;
    SymbolType type;

    bool operator<(const Symbol &x) const { return name < x.name; }

    Symbol(std::string symbolName, SymbolType symbolType) {
        name = symbolName;
        type = symbolType;
    }

    Symbol() {};

    void print() {
        std::cout<<"name "<<name<<" type "<<type;
    }
};

struct Production {
    std::vector<Symbol> production;
    Symbol lhs;

    void print() {
        std::cout <<"current production  ";
        for (Symbol symbol : production) {
            std::cout<<symbol.name<<"  type  "<<symbol.type<<"  ";
        }
        std::cout<<std::endl;
    }
};
struct ParsingTable {
    std::map<Symbol, std::map<Symbol, Production>> table;
};

class CFGParser {
public:
   static std::map<Symbol, std::vector<Production>> getCFGRules(std::string rulesFileName, std::string propertiesFileName);
private:
    CFGParser();
    static std::ifstream openFile (std::string fileName);
    static void parseLine(std::string &line, std::map <Symbol, std::vector<Production>> *rules);
    static std::vector<Production> calculateProductions(std::string &rhs);
    static void loadProperties(std::string propertiesFileName,
                               Properties::PropertiesData &propertiesData);
    static void handleFileNotFound(std::ifstream &file);
    static void errorRoutine();
};


#endif //COMPILER_CFGPARSER_H

