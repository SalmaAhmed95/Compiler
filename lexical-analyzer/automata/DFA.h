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

    /**
     * @param type state type (Accepted, PHI, Intermediate)
     * @param precedence state precedence for matching race condition
     * @param identifier identifier
     */
    stateID createNode(StateType type, int precedence, std::string tokenClass);
};

#endif //COMPLIER_DFA_H
