#ifndef COMPLIER_CFG_H
#define COMPLIER_CFG_H

#include <map>
#include <string>

#include <map>
#include <vector>


#define EPSILONSYMBOl "\\L"

enum SymbolType {
    TERMINAL, NON_TERMINAL, START, EPSILON
};


struct Symbol {
    std::string name;
    SymbolType type;

    bool operator<(const Symbol &x) const { return name < x.name; }

    Symbol(std::string symbolName, SymbolType symbolType) {
        this->name = symbolName;
        this->type = symbolType;
    }
};

struct Production {
    std::vector<Symbol> production;
    Production(std::vector<Symbol> s){
        this->production = s;
    }
};

class CFGParser {
public:
    static std::map<Symbol, std::vector<Production>>
    getCFGRules(std::string fileName);

private:
    CFGParser();
};

#endif
