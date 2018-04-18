#include <map>
#include <set>
#include <vector>
#include "CFGParser.h"

#define END "`"

class Grammar {

public:
    void getGrammerTable(std::string fileName);


private:
    std::map<Symbol, std::vector<Symbol>> first, follow;
    std::set<Symbol> terminals, nonTerminals;
    //TODO take this map from return of CFGParser
    static std::map<Symbol, std::vector<Production>> productions;

    void constructFollowSet();

    std::vector<Symbol> getFollow(Symbol t);
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

