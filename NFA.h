//
// Created by karfass on 14/03/18.
//

#ifndef COMPLIER_NFA_H
#define COMPLIER_NFA_H

#include<string>
#include <vector>
#include "Automata.h"
#include "NfaNode.h"


class NFA : public Automata {
public:
    virtual stateID createNode() = 0;

    std::vector<stateID> getTransitions(stateID curState, char transition);

    std::vector<TransEdgesNfa> getTransitions();

};

#endif //COMPLIER_NFA_H
