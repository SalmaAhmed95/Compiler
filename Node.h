//
// Created by karfass on 14/03/18.
//

#ifndef COMPLIER_NODE_H
#define COMPLIER_NODE_H

#include <map>
#include <vector>
#include <set>

typedef int stateID;

struct Edge {
    stateID from;
    stateID to;
    char transition;
};

struct AcceptanceSpec {
    int precedence;
    std::string *type;
};

struct TransEdgesNfa {
    char transition;
    std::vector<stateID> nextStates;
};

struct TransEdgesDfa {
    char transition;
    int nextState;
};


class Node {

public:

    virtual Node() = 0;

    void setAcceptanceState(AcceptanceSpec *spec);

    virtual void addTransition(stateID node_to, char transition) = 0;


protected:
    stateID ID;
    bool acceptanceState;
    AcceptanceSpec spec;

    Node(stateID id);
};

#endif //COMPLIER_NODE_H
