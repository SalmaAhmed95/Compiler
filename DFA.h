//
// Created by karfass on 14/03/18.
//

#ifndef COMPLIER_NFA_H
#define COMPLIER_NFA_H

#include<string>
#include <vector>
#include "Automata.h"
#include "DfaNode.h"


class DFA : public Automata {
public:
    virtual stateID createNode() = 0;

};

#endif //COMPLIER_NFA_H
