//
// Created by karfass on 14/03/18.
//

#ifndef COMPLIER_DFA_H
#define COMPLIER_DFA_H

#include<string>
#include <vector>
#include "Automata.h"
#include "DfaNode.h"


class DFA : public Automata {
public:
    stateID createNode();
    stateID createNode(StateType type, int precendence, std::string *identifier);

};

#endif //COMPLIER_DFA_H
