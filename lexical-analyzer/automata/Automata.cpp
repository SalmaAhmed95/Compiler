//
// Created by karfass on 15/03/18.
//

#include "Automata.h"

Automata::Automata() : lastNodeID(0) {}

void Automata::addTransition(char transition, stateID from, stateID to) {
  Node *fromNode = graph[from];
  fromNode->addTransition(to, transition);
  attributes.insert(transition);
}

bool Automata::isAccepted(stateID curState) {
  Node *curNode = graph[curState];
  return curNode->isAccepted();
}

bool Automata::isPHI(stateID curState) {
  Node *curNode = graph[curState];
  return curNode->isPHI();
}

int Automata::getPrecedence(stateID curState) {
  Node *curNode = graph[curState];
  return curNode->getPrecedence();
}

std::string Automata::getTokenClass(stateID curState) {
  Node *curNode = graph[curState];
  return curNode->getTokenClass();
}

stateID Automata::getRootID() { return ROOT_ID; }

std::set<char> Automata::getAllAttributes() { return attributes; }

stateID Automata::getNumberOfStates() { return lastNodeID; }

std::vector<stateID> Automata::getTransitions(stateID curState,
                                              char transition) {
  Node *curNode = graph[curState];
  return curNode->getTransitions(transition);
}

std::vector<TransEdges> Automata::getTransitions(stateID curState) {
  Node *curNode = graph[curState];
  return curNode->getTransitions();
}

void Automata::setStateSpec(stateID nodeId, int precedence,
                            std::string tokenClass, StateType stateType) {
  Node *node = graph[nodeId];
  node->setStateSpec(precedence, tokenClass, stateType);
}
