//
// Created by salma on 18/04/18.
//

#include "Grammar.h"
#include <iostream>

ParsingTable *Grammar::getGrammarTable(std::string fileName) {
    std::map<Symbol, std::vector<Production>> rules = CFGParser::getCFGRules(fileName, "properties.ini");
    for (auto rule : rules) {
        std::cout << rule.first.name << "  TYPE  " << rule.first.type << ">>";
        for (auto prod : rule.second) {
            prod.print();
        }
    }
    constructNonTerminals(rules);
    constructTerminals(rules);
    constructFirst(rules);
    std::cout << std::endl << "******First Sets******" << std::endl;
    printSets(first);
    constructFollowSet(rules);
    std::cout << std::endl << "******Follow Sets******" << std::endl;
    printSets(follow);
    constructParsingTable(rules);
    return parsingTable;
}

void Grammar::constructNonTerminals(
        std::map<Symbol, std::vector<Production>> rules) {
    for (auto it = rules.begin(); it != rules.end(); it++) {
        nonTerminals.insert(it->first);
        if (it->first.type == START) {
            parsingTable->setStartSymbol(it->first);
            follow[it->first].insert(Symbol(END, TERMINAL));
        }
    }
}

void Grammar::constructTerminals(
        std::map<Symbol, std::vector<Production>> rules) {
    for (auto it = rules.begin(); it != rules.end(); it++) {
        std::vector<Production> productions = it->second;
        for (auto prod : productions) {
            std::vector<Symbol> symbols = prod.production;
            for (auto symbol : symbols) {
                if (symbol.type == TERMINAL) {
                    terminals.insert(symbol);
                    first[symbol].insert(symbol);
                } else if (symbol.type == EPSILON) {
                    first[symbol].insert(symbol);
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
        if (node->getDependencyCount() == 0) {
            nonTerminalsQueue.push(node);
        }
    }
    int nonTerminalsCount = nonTerminals.size();
    while (!nonTerminalsQueue.empty()) {
        ProductionNode *currentNode = nonTerminalsQueue.front();
        nonTerminalsCount--;
        if (nonTerminalsCount < 0) {
            break;
        }
        nonTerminalsQueue.pop();
        std::vector<Production> productions = rules[currentNode->getSymbol()];
        for (auto prod : productions) {
            std::vector<Symbol> symbols = prod.production;
            bool stop = false;
            for (auto symbol : symbols) {
                if (symbol.type == TERMINAL || symbol.type == EPSILON) {
                    first[currentNode->getSymbol()].insert(symbol);
                    stop = true;
                } else if (graph[symbol] != NULL) {
                    ProductionNode *nextNode = graph[symbol];
                    first[currentNode->getSymbol()].insert(first[symbol].begin(),
                                                           first[symbol].end());
                    stop = !nextNode->containsEps();
                } else {
                    exit(0);
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
            dependent->changeDependencies(-1);
            if (dependent->getDependencyCount() == 0) {
                nonTerminalsQueue.push(dependent);
            }
        }
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
                    dependentNode->changeDependencies(1);
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

void Grammar::constructFollowSet(std::map<Symbol, std::vector<Production>> rules) {
    bool update = true;
    while (update) {
        update = false;
        for (auto it = rules.begin(); it != rules.end(); it++) {
            std::vector<Production> rhsRules = it->second;
            for (auto rule : rhsRules) {
                std::vector<Symbol> symbols = rule.production;
                std::set<Symbol> followSet;
                for (int i = symbols.size() - 1; i >= 0; i--) {
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

void Grammar::constructParsingTable(std::map<Symbol, std::vector<Production>> rules) {
    for (auto it = rules.begin(); it != rules.end(); it++) {
        std::vector<Production> productions = rules[it->first];
        for (auto prod : productions) {
            std::vector<Symbol> symbols = prod.production;
            if (hasEpsilon(first[symbols[0]])) {
                for (auto terminal : follow[it->first]) {
                    if (!parsingTable->isEmpty(it->first, terminal)) {
                        std::cout << ErrorHandler::errors[ErrorHandler::notLL1Error];
                        exit(0);
                    }
                    parsingTable->insertProduction(it->first, terminal, prod);
                }
            } else {
                for (auto terminal : first[symbols[0]]) {
                    if (!parsingTable->isEmpty(it->first, terminal)) {
                        std::cout << ErrorHandler::errors[ErrorHandler::notLL1Error];
                        exit(0);
                    }
                    parsingTable->insertProduction(it->first, terminal, prod);
                }
            }
        }
    }
    addSyncEntries(follow);
}

void Grammar::addSyncEntries(std::map<Symbol, std::set<Symbol>> follow) {
    Production sync;
    sync.production.push_back(Symbol(SYNC, TERMINAL));
    for (auto f : follow) {
        for (auto s : f.second) {
            if (parsingTable->isEmpty(f.first, s))
                parsingTable->insertProduction(f.first, s, sync);
            else if (parsingTable->parsingTable[f.first][s].production[0].type == EPSILON)
                continue;
            else
                parsingTable->insertProduction(f.first, s, sync);

        }
    }
}

void Grammar::printSets(std::map<Symbol, std::set<Symbol>> set) {
    for (auto f : set) {
        std::cout << f.first.name << " >>  ";
        for (auto s : f.second) {
            std::cout << s.name << " ";
        }
        std::cout << std::endl;
    }
}


