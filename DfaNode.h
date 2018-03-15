//
// Created by karfass on 15/03/18.
//

#ifndef COMPLIER_DFANODE_H
#define COMPLIER_DFANODE_H

#include "Node.h"


class DfaNode : public Node {

public:

    virtual DfaNode();

    virtual DfaNode(stateID id);

    virtual void addTransition(stateID node_to, char transition);

    virtual std::vector<TransEdgesDfa> getTransitions();

    virtual std::vector<stateID> getCertainTransitions(char transition);

private:

    std::map<char, stateID> transitions;
};


#endif //COMPLIER_DFANODE_H
