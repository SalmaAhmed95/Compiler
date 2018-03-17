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

stateID DFA::createNode(StateType type, int precendence, std::string *identifier){
    StateSpec newSpec;
    newSpec.identiifer = *identifier;
    newSpec.stateType = type;
    newSpec.precedence = precendence;
    Node* newNode = new DfaNode(lastNodeID, &newSpec);
    DFA::graph.push_back(newNode);
    DFA::lastNodeID++;
    return (DFA::lastNodeID - 1);
}