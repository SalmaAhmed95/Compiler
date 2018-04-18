#include "Grammar.h"

void Grammar::getGrammerTable(std::string fileName) {}

std::set<Symbol>
Grammar::getTerminals(std::map<Symbol, std::vector<Production>> rules) {
  std::set<Symbol> terminals;
  for (auto it = rules.begin(); it != rules.end(); it++) {
    terminals.insert(it->first);
  }
  return terminals;
}

std::set<Symbol>
Grammar::getNonTerminals(std::map<Symbol, std::vector<Production>> rules) {
  std::set<Symbol> nonTerminals;
  for (auto it = rules.begin(); it != rules.end(); it++) {
    std::vector<Production> productions = it->second;
    for (auto prod : productions) {
      std::vector<Symbol> symbols = prod.production;
      for (auto symbol : symbols) {
        if (symbol.type == TERMINAL) {
          nonTerminals.insert(symbol);
        }
      }
    }
  }
  return nonTerminals;
}
