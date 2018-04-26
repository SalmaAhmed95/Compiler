//
// Created by salma on 18/04/18.
//

#include "Grammar.h"
#include "ParsingTable.h"
#include <iostream>

ParsingTable Grammar::getGrammarTable(std::string fileName) {
    std::map<Symbol, std::vector<Production>> rules = CFGParser::getCFGRules(fileName ,"properties.ini");
//    Symbol e("E", START);
//    Symbol ed("ED", NON_TERMINAL);
//    Symbol t("T", NON_TERMINAL);
//    Symbol td("TD", NON_TERMINAL);
//    Symbol f("F", NON_TERMINAL);
//    Symbol eps("\\L", EPSILON);
//    Symbol bo("(", TERMINAL);
//    Symbol bc(")", TERMINAL);
//    Symbol id("id", TERMINAL);
//    Symbol star("*", TERMINAL);
//    Symbol plus("+", TERMINAL);
//    Production p1, p2, peps, p3, p4, p5, p6;
//    peps.production.push_back(eps);
//    p1.production.push_back(t);
//    p1.production.push_back(ed);
//    p2.production.push_back(plus);
//    p2.production.push_back(t);
//    p2.production.push_back(ed);
//    rules[e].push_back(p1);
//    rules[ed].push_back(p2);
//    rules[ed].push_back(peps);
//    p3.production.push_back(f);
//    p3.production.push_back(td);
//    rules[t].push_back(p3);
//    p4.production.push_back(star);
//    p4.production.push_back(f);
//    p4.production.push_back(td);
//    rules[td].push_back(p4);
//    rules[td].push_back(peps);
//    p5.production.push_back(bo);
//    p5.production.push_back(e);
//    p5.production.push_back(bc);
//    p6.production.push_back(id);
//    rules[f].push_back(p5);
//    rules[f].push_back(p6);
    for(auto rule : rules){
        std::cout<<rule.first.name<<">>";
        for(auto prod : rule.second){
            prod.print();
        }
    }
    constructNonTerminals(rules);
    constructTerminals(rules);
    std::cout << std::endl << "First Sets" << std::endl;
    constructFirst(rules);
    constructFollowSet(rules);
    std::cout << std::endl << "Follow Sets" << std::endl;
    printSets(follow);
    constructParsingTable(rules);
    std::cout << std::endl << "Parsing Table" << std::endl;
    printParsingTable(parsingTable);
    return parsingTable;
}

void Grammar::constructNonTerminals(
        std::map<Symbol, std::vector<Production>> rules) {
    for (auto it = rules.begin(); it != rules.end(); it++) {
        terminals.insert(it->first);
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
                    nonTerminals.insert(symbol);
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
        if(nonTerminalsCount < 0) {
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
                    std::cout << symbol.name << std::endl;
                    ProductionNode *currentNode = graph[symbol];

                    stop = !currentNode->containsEps();
                    std::cout << "HERE2" << std::endl;
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
            //TODO if a cell in table has 2 values issue error
            if (hasEpsilon(first[symbols[0]])) {
                for (auto terminal : follow[it->first])
                    parsingTable.insertProduction(it->first, terminal, prod);
            } else {
                for (auto terminal : first[symbols[0]])
                    parsingTable.insertProduction(it->first, terminal, prod);
            }
        }
    }
    addSyncEntries(follow);
}

void Grammar::addSyncEntries(std::map<Symbol, std::set<Symbol>> follow) {
    Production sync;
    sync.production.push_back(Symbol(SYNC,TERMINAL));
    for (auto f : follow) {
        for (auto s : f.second) {
            if(parsingTable.isEmpty(f.first,s))
               parsingTable.insertProduction(f.first,s,sync);
            else if(parsingTable.parsingTable[f.first][s].production[0].type == EPSILON)
                continue;
            else
                parsingTable.insertProduction(f.first,s,sync);

        }
    }
}

void Grammar::printSets(std::map<Symbol, std::set<Symbol>> set) {
    for (auto f : follow) {
        std::cout << f.first.name << " >>  ";
        for (auto s : f.second) {
            std::cout << s.name << " ";
        }
        std::cout << std::endl;
    }
}

void Grammar::printParsingTable(ParsingTable parsingTable) {
    for (auto &outer_map_pair : parsingTable.parsingTable) {
        std::cout << outer_map_pair.first.name << " contains: " << std::endl;
        for (auto &inner_map_pair : outer_map_pair.second) {
            std::cout << inner_map_pair.first.name << ": ";
            for (auto prod: inner_map_pair.second.production)
                std::cout << prod.name << " ";
            std::cout << std::endl;
        }
    }
}

