//
// Created by karfass on 15/03/18.
//

#ifndef COMPLIER_DFANODE_H
#define COMPLIER_DFANODE_H

#include "Node.h"


class DfaNode : public Node {

public:


     DfaNode(stateID id);

    /**
     * @param transition the char of the transition
     * @param node_to the stateId of the sink of the transition
     */
     void addTransition(stateID node_to, char transition);

    /**
     * @return a vector of TransEdges which represents all possible transitions for the current state.
     */
    std::vector<TransEdges> getTransitions();

    /**
     * @param transition a char that represents the transition attribute.
     * @return a vector of size 1 which represents the next state for the given transition.
     */
    std::vector<stateID> getTransitions(char transition);

private:

    std::map<char, stateID> transitions;
};


#endif //COMPLIER_DFANODE_H
