//
// Created by karfass on 15/03/18.
//
#include "NFA.h"
//

stateID NFA ::createNode() {
        Node* newNode = new NfaNode(lastNodeID);
        NFA::graph.push_back(newNode);
        NFA::lastNodeID++;
        return (NFA::lastNodeID - 1);
}

