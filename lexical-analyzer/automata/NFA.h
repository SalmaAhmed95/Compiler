//
// Created by karfass on 14/03/18.
//

#ifndef COMPLIER_NFA_H
#define COMPLIER_NFA_H

#include "Automata.h"
#include "NfaNode.h"
#include <string>
#include <vector>

class NFA : public Automata {
public:
  NFA(int minAsciiCodeValue, int maxAsciiCodeValue);
  stateID createNode();
  stateID createNode(StateType type, int precedence, std::string tokenClass);
  void setNfaRange(int minAsciiCodeValue, int maxAsciiCodeValue);

private:
  int minAsciiCodeValue;
  int maxAsciiCodeValue;
};

#endif // COMPLIER_NFA_H
