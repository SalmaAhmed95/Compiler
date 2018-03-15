//
// Created by karfass on 15/03/18.
//

#ifndef COMPLIER_AUTOMATA_H
#define COMPLIER_AUTOMATA_H


#include "Node.h"

class Automata{

public:

    virtual stateID createNode() = 0;

    void addTransition(Edge *edge);

    void setAcceptance(AcceptanceSpec *acceptanceSpec1);

    AcceptanceSpec *getAcceptance(stateID node);

    stateID getRootID();

    char *getAllAttributes();

    stateID getNumberOfStates();

protected:
    stateID lastNodeID = 0;
    std::vector<Node*> graph;
    char *attributes;

};
#endif //COMPLIER_AUTOMATA_H
