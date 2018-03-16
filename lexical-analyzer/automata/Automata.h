//
// Created by karfass on 15/03/18.
//

#ifndef COMPLIER_AUTOMATA_H
#define COMPLIER_AUTOMATA_H

#include<set>
#include "Node.h"

class Automata{

public:

    virtual stateID createNode() = 0;

    void addTransition(Edge *edge);

    void setAcceptance(stateID id, AcceptanceSpec *acceptanceSpec1);

    AcceptanceSpec *getAcceptance(stateID id);

    stateID getRootID();

    std::set<char> getAllAttributes();

    stateID getNumberOfStates();

    std::vector<stateID> getTransitions(stateID curState, char transition);

    std::vector<TransEdges> getTransitions(stateID curState);

protected:
    stateID lastNodeID = 0;
    std::vector<Node*> graph;
    std::set<char> attributes;

};
#endif //COMPLIER_AUTOMATA_H
