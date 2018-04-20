//
// Created by salma on 18/04/18.
//

#include "Grammar.h"
#include <iostream>

void Grammar::getGrammerTable(std::string fileName) {
  std::map<Symbol, std::vector<Production>> rules;
  Symbol e("E", START);
  Symbol ed("ED", NON_TERMINAL);
  Symbol t("T", NON_TERMINAL);
  Symbol td("TD", NON_TERMINAL);
  Symbol f("F", NON_TERMINAL);
  Symbol eps("`", EPSILON);
  Symbol bo("(", TERMINAL);
  Symbol bc(")", TERMINAL);
  Symbol id("id", TERMINAL);
  Symbol star("*", TERMINAL);
  Symbol plus("+", TERMINAL);
  Production p1, p2, peps, p3, p4, p5, p6;
  peps.production.push_back(eps);
  p1.production.push_back(t);
  p1.production.push_back(ed);
  p2.production.push_back(plus);
  p2.production.push_back(t);
  p2.production.push_back(ed);
  rules[e].push_back(p1);
  rules[ed].push_back(p2);
  rules[ed].push_back(peps);
  p3.production.push_back(f);
  p3.production.push_back(td);
  rules[t].push_back(p3);
  p4.production.push_back(star);
  p4.production.push_back(f);
  p4.production.push_back(td);
  rules[td].push_back(p4);
  rules[td].push_back(peps);
  p5.production.push_back(bo);
  p5.production.push_back(e);
  p5.production.push_back(bc);
  p6.production.push_back(id);
  rules[f].push_back(p5);
  rules[f].push_back(p6);
  constructFirst(rules);
}

void Grammar::constructTerminals(
    std::map<Symbol, std::vector<Production>> rules) {
  std::set<Symbol> terminals;
  for (auto it = rules.begin(); it != rules.end(); it++) {
    terminals.insert(it->first);
    std::cout << it->first.name << '\n';
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
          std::cout << symbol.name << '\n';
        }
      }
    }
  }
}

void Grammar::constructFirst(std::map<Symbol, std::vector<Production>> rules) {
  std::vector<ProductionNode *> nodes;
  std::map<Symbol, ProductionNode *> graph;
  buildGraph(rules, nodes, graph);
  std::queue<ProductionNode *> nonTerminalsQueue;
  for (auto node : nodes) {
    if (node->getDependenceyCount() == 0) {
      nonTerminalsQueue.push(node);
    }
  }
  while (!nonTerminalsQueue.empty()) {
    ProductionNode *currentNode = nonTerminalsQueue.front();
    nonTerminalsQueue.pop();
    std::vector<Production> productions = rules[currentNode->getSymbol()];
    for (auto prod : productions) {
      std::vector<Symbol> symbols = prod.production;
      bool stop = false;
      for (auto symbol : symbols) {
        if (symbol.type == TERMINAL || symbol.type == EPSILON) {
          first[currentNode->getSymbol()].insert(symbol);
          stop = true;
        } else {
          ProductionNode *nextNode = graph[symbol];
          first[currentNode->getSymbol()].insert(first[symbol].begin(),
                                                 first[symbol].end());
          stop = !(nextNode->containsEps());
        }
        if (stop) {
          break;
        }
      }
      if (!stop) {
        struct Symbol e("\\L", EPSILON);
        first[currentNode->getSymbol()].insert(e);
      }
    }
    std::vector<ProductionNode *> dependents = currentNode->getDependents();
    for (auto dependent : dependents) {
      dependent->changeDependecies(-1);
      if (dependent->getDependenceyCount() == 0) {
        nonTerminalsQueue.push(dependent);
      }
    }
  }
  for (auto it = first.begin(); it != first.end(); it++) {
    std::cout << it->first.name << ':';
    std::set<Symbol> f = it->second;
    for (auto x : f) {
      std::cout << x.name << '-';
    }
    std::cout << '\n';
  }
}

void Grammar::buildGraph(std::map<Symbol, std::vector<Production>> rules,
                         std::vector<ProductionNode *> &nodes,
                         std::map<Symbol, ProductionNode *> &graph) {
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
        } else if (symbol.type != EPSILON) {
          ProductionNode *currentNode = graph[symbol];
          stop = !currentNode->containsEps();
          currentNode->addDependent(dependentNode);
          dependentNode->changeDependecies(1);
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
      if (symbols.size() == 1 && symbols[0].type == EPSILON) {
        node->setEps();
      }
    }
  }
}

/*constructs the follow set for every non terminal*/
void Grammar::constructFollowSet() {
  bool update = true;
  while (update) {
    update = false;
    for (auto it = productions.begin(); it != productions.end(); it++) {
      std::vector<Production> rhsRules = it->second;
      for (auto rule : rhsRules) {
        std::vector<Symbol> symbols = rule.production;
        std::set<Symbol> followSet;
        for (int i = symbols.size() - 1; i >= 0; i++) {
          Symbol symbol = symbols[i];
          if (symbol.type == START)
            followSet.insert(Symbol(END, TERMINAL));
          if (symbol.type == EPSILON)
            continue;
          else if (isTerminal(symbol)) {
            followSet.clear();
            followSet.insert(symbol);
          } else {

            if (i == symbols.size() - 1)
              followSet.insert(follow[it->first].begin(),
                               follow[it->first].end());
            int prevSize = follow[symbol].size();
            follow[symbol].insert(followSet.begin(), followSet.end());
            if (prevSize < follow[symbol].size())
              update = true;

            if (!hasEpsilon(first[symbol])) {
              followSet.clear();
            }
            followSet.insert(first[symbol].begin(), first[symbol].end());
            followSet.erase(Symbol(EPSILONSYMBOl, EPSILON));
          }
        }
      }
    }
  }
}

bool Grammar::isTerminal(Symbol t) {
  if (t.type == TERMINAL)
    return true;
  return false;
}

bool Grammar::hasEpsilon(std::set<Symbol> first) {
  Symbol epsilon(EPSILONSYMBOl, EPSILON);
  if (first.find(epsilon) != first.end())
    return true;
  return false;
}

void Grammar::printSets(std::map<Symbol, std::set<Symbol>> set) {
  for (auto f : follow) {
    std::cout << f.first.name << ">>>>";
    for (auto s : f.second) {
      std::cout << s.name << " ";
    }
    std::cout << std::endl;
  }
}
