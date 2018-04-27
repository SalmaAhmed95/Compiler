

#ifndef COMPILER_CFGPARSER_H
#define COMPILER_CFGPARSER_H

#include <map>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include "../lexical-analyzer/grammar-parser/Properties.hpp"
#include "../error/ErrorHandler.h"
#include <fstream>
#include <set>
#include <climits>
#include "../utils/StringUtils.h"

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

    Symbol() {
        name = "";
        type = NON_TERMINAL;
    }

    bool operator==(const Symbol &rhs) const {
        return name == rhs.name && (type == rhs.type || (type == START && rhs.type == NON_TERMINAL));
    }

    bool operator!=(const Symbol &rhs) const {
        return name != rhs.name || (type != rhs.type);
    }

    std::string toString() {
        return name;
    }

    void print() {
        std::cout << "name " << name << " type " << type;
    }
};

struct Production {
    std::vector<Symbol> production;

    std::string toString() {
        std::string string;
        for (int i = 0; i < production.size(); i++) {
            string = string + production[i].name + ((i == production.size() - 1) ? "" : " ");
        }
        return string;
    }

    void print() {
        std::cout << "current production  ";
        for (Symbol symbol : production) {
            std::cout << symbol.name << "  type  " << symbol.type << "  ";
        }
        std::cout << std::endl;
    }
};

class CFGParser {
public:
    static std::map<Symbol, std::vector<Production>>
    getCFGRules(std::string rulesFileName, std::string propertiesFileName);

private:
    CFGParser();

    /*parses the new rule scanned rule to LHS and RHS*/
    static void parseLine(std::string &line, std::string &startSymbolName, std::map <Symbol, std::vector<Production>> *rules);

    static bool checkNonTerminalValidity(std::string &lhs);

    /*parses the RHS of the rule to non terminals and terminals*/
    static std::vector<Production> calculateProductions(std::string &rhs, std::string &startSymbolName);

    /*checks that all the non terminals are defined */
    static bool checkRulesValidity(std::map <Symbol, std::vector<Production>> *rules);

    /*perform the left recursive elimination algorithm for all the defined rules*/
    static void executeLeftRecursiveElimination(std::map <Symbol, std::vector<Production>> *rules);

    /*utility function for the left recursive elimination algorithm that takes two symbols and whether it's left recursive
     * or not it decides to push it to alpha productions or beta productions
     * */
    static bool checkLeftRecursive(Symbol &first, Symbol &rhsSymbol, Production &curRule,
                                  std::vector<Production> *alpha, std::vector<Production> *beta);

    /*perform the left factoring algorithm  all the defined rules*/
    static void executeLeftFactoring(std::map<Symbol,std::vector<Production>> *curRules);

    /*utility function for left factoring algorithm that checks if certain rule needs left factoring or not
     * and pushes the new rules to a temp data structure*/
    static void checkLeftFactoring(std::map <Symbol, std::vector<Production>> *tempRules, std::map<Symbol, std::vector<Production>> *curRules,
                                   std::map <Symbol, std::vector<Production>>::iterator it);

    /*utility function that for a rule that needs left factoring, gets the longest common prefix , generates new rules
     * and returns iterator to the new generated rule*/
    static std::map <Symbol, std::vector<Production>>::iterator performLeftFactoring (std::map<Symbol, std::vector<Production>> *tempRules,
                                                                                      std::map<Symbol,std::vector<Production>> *curRules,
                                                                                      std::vector<Production> &productions,
                                                                                      Symbol firstSymbol);

    static std:: string getNewSymbolName (std::map<Symbol,std::vector<Production>> *curRules,
                                          std::map<Symbol,std::vector<Production>> *tempRules, std::string &firstSymbolName);

    static std::ifstream *openFile (std::string fileName);

    static void loadProperties(std::string propertiesFileName,
                               Properties::PropertiesData &propertiesData);
    static void handleFileNotFound(std::ifstream &file);

    static void errorRoutine(ErrorHandler::Error);

};


#endif //COMPILER_CFGPARSER_H

