//
// Created by salma on 18/04/18.
//

#include "Grammar.h"

void Grammar::constructTerminals(
    std::map<Symbol, std::vector<Production>> rules) {
  std::set<Symbol> terminals;
  for (auto it = rules.begin(); it != rules.end(); it++) {
    terminals.insert(it->first);
  }
}

void Grammar::constructNonTerminals(
    std::map<Symbol, std::vector<Production>> rules) {
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
}

std::vector<ProductionNode *>
Grammar::buildGraph(std::map<Symbol, std::vector<Production>> rules) {
  std::vector<ProductionNode *> nodes;
  std::map<Symbol, ProductionNode *> graph;
  buildNodes(nodes, graph, rules);
  for (auto it = rules.begin(); it != rules.end(); it++) {
    ProductionNode *dependentNode = graph[it->first];
    std::vector<Production> productions = it->second;
    for (auto prod : productions) {
      std::vector<Symbol> symbols = prod.production;
      for (auto symbol : symbols) {
        bool stop = false;
        if (symbol.type == TERMINAL) {
          stop = true;
        } else {
          ProductionNode *currentNode = graph[symbol];
          stop = !currentNode->containsEps();
          currentNode->addDependent(dependentNode);
        }
        if (stop) {
          break;
        }
      }
    }
  }
}

void Grammar::buildNodes(std::vector<ProductionNode *> &nodes,
                         std::map<Symbol, ProductionNode *> &graph,
                         std::map<Symbol, std::vector<Production>> rules) {
  for (auto it = rules.begin(); it != rules.end(); it++) {
    ProductionNode *node;
    if (!graph.count(it->first)) {
      node = new ProductionNode(it->first);
      graph[it->first] = node;
      nodes.push_back(node);
    } else {
      node = graph[it->first];
    }
    std::vector<Production> productions = it->second;
    for (auto prod : productions) {
      std::vector<Symbol> symbols = prod.production;
      if (symbols.size() == 1 && symbols[0].type == EPSILION) {
        node->setEps();
      }
    }
  }
}

/*constructs the follow set for every non terminal*/
void Grammar::constructFollowSet() {
  for (auto t : nonTerminals) {
    std::vector<Symbol> followSet = getFollow(t);
    follow.insert(std::pair<Symbol, std::vector<Symbol>>(t, followSet));
  }
}

/* sets the follow set for a certain nonTerminal t
 * then pushes the symbol along with its follow set
 * to the map of follow**/
std::vector<Symbol> Grammar::getFollow(Symbol t) {
  std::vector<Symbol> followSet;
  if (t.type == START) {
    Symbol end(END, TERMINAL);
    followSet.push_back(end);
  }
  for (auto it = productions.begin(); it != productions.end(); it++) {
  }
}
