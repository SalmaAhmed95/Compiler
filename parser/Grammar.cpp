//
// Created by salma on 18/04/18.
//

#include <iostream>
#include "Grammar.h"


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
                    if(symbol.type == START)
                        followSet.insert(Symbol(END,TERMINAL));
                    if (symbol.type == EPSILON)
                        continue;
                    else if (isTerminal(symbol)) {
                        followSet.clear();
                        followSet.insert(symbol);
                    } else {

                        if (i == symbols.size() - 1)
                            followSet.insert(follow[it->first].begin(), follow[it->first].end());
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
    for(auto f: follow){
        std::cout<<f.first.name<<">>>>";
        for(auto s: f.second){
            std::cout<<s.name<<" ";
        }
        std::cout<<std::endl;
    }
}
