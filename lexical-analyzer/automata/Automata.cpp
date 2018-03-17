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

void Automata::setAcceptance(stateID id, AcceptanceSpec *acceptanceSpec1) {
  Node *curNode = graph[id];
  curNode->setAcceptanceState(acceptanceSpec1);
}

AcceptanceSpec *Automata::getAcceptance(stateID id) {
  Node *curNode = graph[id];
  return curNode->getAcceptance();
}

stateID Automata::getRootID() { return 0; }

std::set<char> Automata::getAllAttributes() { return attributes; }

stateID Automata::getNumberOfStates() { return lastNodeID; }

std::vector<stateID> Automata::getTransitions(stateID curState,
                                              char transition) {
  Node *curNode = graph[curState];
  return curNode->getTransitions(transition);
}

std::vector<TransEdges> Automata :: getTransitions(stateID curState) {
    Node* curNode = graph[curState];
    return curNode->getTransitions();
}

bool Automata::isAcceptance(stateID stateId) {
    //TODO implement this function
    return false;
}

bool Automata::setAcceptance(stateID stateId, bool acceptance) {

    return false;
}
