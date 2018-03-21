//
// Created by karfass on 15/03/18.
//
#include "NFA.h"
//

NFA::NFA(int minAsciiCodeValue, int maxAsciiCodeValue){
    NFA::minAsciiCodeValue = minAsciiCodeValue;
    NFA::maxAsciiCodeValue = maxAsciiCodeValue;
}

stateID NFA::createNode() {
  Node *newNode = new NfaNode(lastNodeID, minAsciiCodeValue, maxAsciiCodeValue);
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
  Node *newNode = new NfaNode(lastNodeID, &newSpec, minAsciiCodeValue, maxAsciiCodeValue);
  NFA::graph.push_back(newNode);
  NFA::lastNodeID++;
  return (NFA::lastNodeID - 1);
}

void NFA::setNfaRange(int minAsciiCodeValue, int maxAsciiCodeValue){

}