#include <CFGParser.h>
#include <map>
#include <set>
#include <vector>

class Grammar {

private:
  std::map<Symbol, std::vector<Symbol>> first, follow;
  std::set<Symbol> terminals, nonTerminals;
}
