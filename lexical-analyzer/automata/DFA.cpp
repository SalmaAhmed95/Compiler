//
// Created by karfass on 15/03/18.
//
#include "DFA.h"
//

stateID DFA::createNode() {
  Node *newNode = new DfaNode(DFA::lastNodeID);
  DFA::graph.push_back(newNode);
  DFA::lastNodeID++;
  return (DFA::lastNodeID - 1);
}

stateID DFA::createNode(StateType type, int precedence,
                        std::string tokenClass) {
  StateSpec newSpec;
  newSpec.tokenClass = tokenClass;
  newSpec.stateType = type;
  newSpec.precedence = precedence;
  Node *newNode = new DfaNode(lastNodeID, &newSpec);
  DFA::graph.push_back(newNode);
  DFA::lastNodeID++;
  return (DFA::lastNodeID - 1);
}
