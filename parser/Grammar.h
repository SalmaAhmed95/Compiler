#include <CFGParser.h>
#include <map>
#include <set>
#include <vector>

class Grammar {

<<<<<<< HEAD
public:
  void getGrammerTable(std::string fileName);

=======
>>>>>>> ec9264f72672440ea29412e127ed1a174879ee96
private:
  std::map<Symbol, std::vector<Symbol>> first, follow;
  std::set<Symbol> terminals, nonTerminals;
}
<<<<<<< HEAD

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
=======
>>>>>>> ec9264f72672440ea29412e127ed1a174879ee96
