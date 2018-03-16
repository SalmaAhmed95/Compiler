//
// Created by karfass on 15/03/18.
//

#include "Automata.h"

void Automata::addTransition(Edge *edge) {
    int from = edge->from;
    int to = edge->to;
    Node *fromNode = graph[from];
    fromNode->addTransition(to, edge->transition);
    attributes.insert(edge->transition);
}

void Automata::setAcceptance(stateID id,AcceptanceSpec *acceptanceSpec1){
    Node* curNode = graph[id];
    curNode->setAcceptanceState(acceptanceSpec1);
}

AcceptanceSpec* Automata::getAcceptance(stateID id){
    Node* curNode = graph[id];
    return curNode->getAcceptance();
}

stateID Automata ::getRootID() {
    return 0;
}


std::set<char> Automata :: getAllAttributes() {
    return attributes;
}

stateID Automata :: getNumberOfStates() {
    return lastNodeID;
}


std::vector<stateID> Automata :: getTransitions(stateID curState, char transition){
    Node* curNode = graph[curState];
    return curNode->getTransitions(transition);
}

std::vector<TransEdges> Automata :: getTransitions(stateID curState) {
    Node* curNode = graph[curState];
    return curNode->getTransitions();
}