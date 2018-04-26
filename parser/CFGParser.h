

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
    Symbol(){
        name = "";
        type = NON_TERMINAL;
    }
    bool operator== (const Symbol& rhs) const{
        return name == rhs.name && (type == rhs.type || (type == START && rhs.type == NON_TERMINAL));
    }


    bool operator!= (const Symbol& rhs) const{
        return name != rhs.name || (type != rhs.type);
    }

    std::string toString () {
        return name;
    }

    void print() {
        std::cout<<"name "<<name<<" type "<<type;
    }
};

struct Production {
    std::vector<Symbol> production;

    std::string toString() {
        std::string string;
        for (Symbol symbol: production) {
            string += symbol.name;
        }
        return string;
    }

    void print() {
        std::cout <<"current production  ";
        for (Symbol symbol : production) {
            std::cout<<symbol.name<<"  type  "<<symbol.type<<"  ";
        }
        std::cout<<std::endl;
    }
};

class CFGParser {
public:
   static std::map<Symbol, std::vector<Production>> getCFGRules(std::string rulesFileName, std::string propertiesFileName);
private:
    CFGParser();
    static std::ifstream *openFile (std::string fileName);
    static void parseLine(std::string &line, std::string &startSymbolName, std::map <Symbol, std::vector<Production>> *rules);
    static std::vector<Production> calculateProductions(std::string &rhs, std::string &startSymbolName);
    static void loadProperties(std::string propertiesFileName,
                               Properties::PropertiesData &propertiesData);
    static void handleFileNotFound(std::ifstream &file);
    static bool checkRulesValidaty(std::map <Symbol, std::vector<Production>> *rules);
    static void performLeftRecursiveElimination(std::map <Symbol, std::vector<Production>> *rules);
    static bool checkLeftRecursive(Symbol &first, Symbol &rhsSymbol, Production &curRule,
                                  std::vector<Production> *alpha, std::vector<Production> *beta);
    static void excuteLeftFactoring(std::map<Symbol,std::vector<Production>> *curRules);
    static std::map <Symbol, std::vector<Production>>::iterator performLeftFactoring (std::map<Symbol, std::vector<Production>> *tempRules,
                                                                                 std::map<Symbol,std::vector<Production>> *curRules, std::vector<Production> &productions,
                                                                                 Symbol firstSymbol);
    static void checkLeftFactoring(std::map <Symbol, std::vector<Production>> *tempRules, std::map<Symbol, std::vector<Production>> *curRules,
                                   std::map <Symbol, std::vector<Production>>::iterator it);
    static void errorRoutine();
    static std:: string getNewSymbolName (std::map<Symbol,std::vector<Production>> *curRules,
                                          std::map<Symbol,std::vector<Production>> *tempRules, std::string &firstSymbolName);
};


#endif //COMPILER_CFGPARSER_H

