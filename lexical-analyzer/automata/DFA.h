//
// Created by karfass on 14/03/18.
//

#ifndef COMPLIER_DFA_H
#define COMPLIER_DFA_H

#include "Automata.h"
#include "DfaNode.h"
#include <string>
#include <vector>

class DFA : public Automata {
public:
  stateID createNode();
  stateID createNode(StateType type, int precedence, std::string tokenClass);
};

#endif // COMPLIER_DFA_H
