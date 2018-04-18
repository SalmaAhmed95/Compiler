
#include <map>
#include <set>
#include <vector>
#include "CFGParser.h"

#define END "`"

class Grammar {

public:
    void getGrammerTable(std::string fileName);

    void printSets(std::map<Symbol, std::set<Symbol>> set);
private:
    std::map<Symbol, std::set<Symbol>> first, follow;
    std::set<Symbol> terminals, nonTerminals;

    std::set<Symbol>
    getTerminals(std::map<Symbol, std::vector<Production>> rules);

    std::set<Symbol>
    getNonTerminals(std::map<Symbol, std::vector<Production>> rules);

    bool isTerminal(Symbol t);
    bool hasEpsilon(std::set<Symbol> first);

    //TODO take this map from return of CFGParser
    std::map<Symbol, std::vector<Production>> productions;
    void constructFollowSet();

};

/*

getTable (file){
  get rules
  construct terminals
  first
  follow(first)
  constructTable
}

*/

