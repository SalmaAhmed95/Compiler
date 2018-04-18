#ifndef COMPLIER_GRAMMAR_H
#define COMPLIER_GRAMMAR_H
#include "CFGParser.h"
#include "ProductionNode.h"
#include <map>
#include <set>
#include <vector>

#define END "`"

class Grammar {

public:
  void getGrammerTable(std::string fileName);

private:
  std::map<Symbol, std::vector<Symbol>> first, follow;
  std::set<Symbol> terminals, nonTerminals;

  void constructTerminals(std::map<Symbol, std::vector<Production>> rules);

  void constructNonTerminals(std::map<Symbol, std::vector<Production>> rules);

  // TODO take this map from return of CFGParser
  std::map<Symbol, std::vector<Production>> productions;

  void constructFollowSet();

  std::vector<Symbol> getFollow(Symbol t);

  std::vector<ProductionNode *>
  buildGraph(std::map<Symbol, std::vector<Production>> rules);
  void buildNodes(std::vector<ProductionNode *> &nodes,
                  std::map<Symbol, ProductionNode *> &graph,
                  std::map<Symbol, std::vector<Production>> rules);
};
#endif
