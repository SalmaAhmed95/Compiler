//
// Created by karfass on 14/03/18.
//

#ifndef COMPLIER_NODE_H
#define COMPLIER_NODE_H

#include <map>
#include <set>
#include <string>
#include <vector>


typedef int stateID;

enum StateType {
    ACCEPTED, PHI, INTERMEDIATE
};

struct Edge {
    stateID from;
    stateID to;
    char transition;
};

struct StateSpec {
    StateType stateType;
    int precedence;
    std::string identiifer;
};

struct TransEdges {
    char transition;
    std::vector<stateID> nextStates;
};

struct TransEdgesDfa {
    char transition;
    int nextState;
};



class Node {

public:
    Node();

    bool isAccepted();

    bool isPHI();

    int getPrecendence();

    std::string getIdentifier();

    virtual void addTransition(stateID node_to, char transition) = 0;

    virtual std::vector<stateID> getTransitions(char transition) = 0;

    virtual std::vector<TransEdges> getTransitions() = 0;

protected:
    stateID ID;
    StateSpec stateSpec;

    Node(stateID id);

    Node(stateID id, StateSpec *spec);

};

#endif // COMPLIER_NODE_H
