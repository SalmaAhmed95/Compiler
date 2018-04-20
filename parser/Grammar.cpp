//
// Created by salma on 18/04/18.
//

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
//void Grammar::constructFollowSet() {
//    for (auto t : nonTerminals) {
//        std::vector<Symbol> followSet = getFollow(t);
//        follow.insert(std::pair<Symbol, std::vector<Symbol>>(t, followSet));
//    }
//}

/* sets the follow set for a certain nonTerminal t
 * then pushes the symbol along with its follow set
 * to the map of follow**/
//std::vector<Symbol> Grammar::getFollow(Symbol t) {
//    std::vector<Symbol> followSet;
//    if (t.type == START) {
//        Symbol end(END, TERMINAL);
//        followSet.push_back(end);
//    }
//    for (auto it = productions.begin(); it != productions.end(); it++) {
//
//    }
//}