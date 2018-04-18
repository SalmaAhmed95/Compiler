//
// Created by salma on 18/04/18.
//

#include "Grammar.h"

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
std::vector <Symbol> followSet;
    if(t.type == START){
        Symbol end(END,TERMINAL);
        followSet.push_back(end);
    }
    for (auto& t : productions) {

    }
}