
#include <string>
#include <unordered_map>
#include <vector>

enum SymbolType { TERMINAL, NON_TERMINAL, EPSILION };

struct Symbol {
  std::string name;
  SymbolType type;
  bool operator<(const Symbol &x) const { return name < x.name; }
};

struct Production {
  std::vector<Symbol> production;
};

class CFGParser {
public:
  static std::unordered_map<Symbol, std::vector<Production>>
  getCFGRules(std::string fileName);

private:
  CFGParser();
};
