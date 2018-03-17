//
// Created by karfass on 15/03/18.
//
#include "DFA.h"
//

stateID DFA ::createNode() {
    Node* newNode = new DfaNode(DFA::lastNodeID);
    DFA::graph.push_back(newNode);
    DFA::lastNodeID++;
    return (DFA::lastNodeID - 1);
}

