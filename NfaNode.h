//
// Created by karfass on 15/03/18.
//

#ifndef COMPLIER_NFANODE_H
#define COMPLIER_NFANODE_H

#include "Node.h"

class NfaNode : public Node {

public:

    virtual NfaNode();

    virtual NfaNode(stateID id);

    virtual void addTransition(stateID node_to, char transition);

    virtual std::vector<TransEdgesNfa> getTransitions();

    virtual std::vector<stateID> getCertainTransitions(char transition);

private:

    std::map<int, std::vector<int> > transisions;


};
#endif //COMPLIER_NFANODE_H
