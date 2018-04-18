#include "CFGParser.h"
#include <map>
#include <set>
#include <vector>

class Grammar {

public:
  void getGrammerTable(std::string fileName);

private:
  std::map<Symbol, std::vector<Symbol>> first, follow;
  std::set<Symbol> terminals, nonTerminals;
  std::set<Symbol>
  getTerminals(std::map<Symbol, std::vector<Production>> rules);
  std::set<Symbol>
  getNonTerminals(std::map<Symbol, std::vector<Production>> rules);
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
