//
// Created by karfass on 15/03/18.
//

#ifndef COMPLIER_DFANODE_H
#define COMPLIER_DFANODE_H

#include "Node.h"


class DfaNode : public Node {

public:


     DfaNode(stateID id);
     DfaNode(stateID id, StateSpec *stateSpec);
     void addTransition(stateID node_to, char transition);
     std::vector<TransEdges> getTransitions();
     std::vector<stateID> getTransitions(char transition);

private:

    std::map<char, stateID> transitions;
};


#endif //COMPLIER_DFANODE_H
