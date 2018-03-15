//
// Created by karfass on 15/03/18.
//
#include "NFA.h"
//
stateID NFA ::createNode() {
        Node* newNode = new NfaNode(Automata::lastNodeID);
        NFA::graph.push_back(newNode);
        NFA::lastNodeID++;
        return (NFA::lastNodeID - 1);
}
//
//void NFA ::addTransition(edge &newEdge) {
//        Node* fromNode = NFA::graph[newEdge.from];
//        fromNode->addTransition(newEdge.to,newEdge.transition);
//}
//
//
//void NFA ::setAcceptanceState(stateID state, acceptanceSpec* spec){
//        Node* fromNode = NFA::graph.[state];
//        fromNode->setsetAcceptanceState(spec);
//}
//
//
//std::vector<stateID> NFA :: getTransitions(stateID curState, char transition){
//      Node* fromNode = NFA::graph[curState];
//      return fromNode->getCertainTransitions(transition);
//}
//
