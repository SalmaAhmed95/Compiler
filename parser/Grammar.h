#include <CFGParser.h>
#include <map>
#include <set>
#include <vector>

class Grammar {

public:
  void getGrammerTable(std::string fileName);

private:
  std::map<Symbol, std::vector<Symbol>> first, follow;
  std::set<Symbol> terminals, nonTerminals;
}

/*

getTable (file){
  get rules
  construct terminals
  first
  follow(first)
  constructTable
}


*/

`
