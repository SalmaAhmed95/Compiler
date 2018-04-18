
#include <string>
#include <vector>
#include <unordered_map>

enum SymbolType { TERMINAL, NON_TERMINAL};

struct Symbol {
    std::string name;
    SymbolType type;
//TODO comparator
};

struct Production {
    std::vector<Symbol> production;
};

class CFGParser {
public:
    static std::unordered_map<Symbol, std::vector<Production>> getCFGRules(std::string fileName);
private:
    CFGParser();

};
