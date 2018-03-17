//
// Created by karfass on 15/03/18.
//
#include "NFA.h"
//

stateID NFA::createNode() {
  Node *newNode = new NfaNode(lastNodeID);
  NFA::graph.push_back(newNode);
  NFA::lastNodeID++;
  return (NFA::lastNodeID - 1);
}

stateID NFA::createNode(StateType type, int precedence,
                        std::string tokenClass) {
  StateSpec newSpec;
  newSpec.tokenClass = tokenClass;
  newSpec.stateType = type;
  newSpec.precedence = precedence;
  Node *newNode = new NfaNode(lastNodeID, &newSpec);
  NFA::graph.push_back(newNode);
  NFA::lastNodeID++;
  return (NFA::lastNodeID - 1);
}
