#ifndef COMPLIER_GRAMMAR_H
#define COMPLIER_GRAMMAR_H
#include "CFGParser.h"
#include "ProductionNode.h"
#include <map>
#include <queue>
#include <set>
#include <vector>

#define END "`"

class Grammar {

public:
  void getGrammerTable(std::string fileName);

private:
  std::map<Symbol, std::set<Symbol>> first, follow;
  std::set<Symbol> terminals, nonTerminals;

  void constructTerminals(std::map<Symbol, std::vector<Production>> rules);

  void constructNonTerminals(std::map<Symbol, std::vector<Production>> rules);

  // TODO take this map from return of CFGParser
  std::map<Symbol, std::vector<Production>> productions;

  void constructFirst(std::map<Symbol, std::vector<Production>> rules);

  void constructFollowSet();

  std::vector<Symbol> getFollow(Symbol t);

  void buildGraph(std::map<Symbol, std::vector<Production>> rules,
                  std::vector<ProductionNode *> &nodes,
                  std::map<Symbol, ProductionNode *> &graph);
  void buildNodes(std::vector<ProductionNode *> &nodes,
                  std::map<Symbol, ProductionNode *> &graph,
                  std::map<Symbol, std::vector<Production>> rules);
};
#endif
