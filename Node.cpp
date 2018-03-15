//
// Created by karfass on 15/03/18.
//
#include "Node.h"

Node ::Node(stateID id) {
    Node::ID = id;
    Node::acceptanceState = false;
}

void Node ::setAcceptanceState(acceptanceSpec* spec){
     Node::acceptanceState = true;
     Node::spec.precedence = spec->precedence;
     Node::spec.type =  new std::string(spec->type);
}

/*void Node::addTransition(stateID node_to, char transition){
    Node::transitions.insert(std::pair<char,stateID>(transition,node_to));
}

std::vector<stateID> Node:: getCertainTransitions(char transition) {
    std::vector<stateID> nextstates;
    std::pair <std::multimap<char,stateID >::iterator, std::multimap<char,stateID >::iterator> ret;
    ret = Node::transitions.equal_range(transition);
    for (std::multimap<char,int>::iterator it=ret.first; it!=ret.second; ++it) {
        nextstates.push_back(it->second);
    }
    return nextstates;
}

std::vector<transEdges> Node :: getTransitions() {
    std::vector<transEdges> allTransitions;
    std::set<char> char_transitions;
    for (std::multimap<char,int>::iterator it=Node::transitions.begin(); it!=Node::transitions.end(); ++it){
            char charT = (*it).first;
            if (char_transitions.find(charT) == char_transitions.end()) {
                char_transitions.insert(charT);
                transEdges newTransition;
                newTransition.transition = charT;
                newTransition.nextStates = getCertainTransitions(charT);
                allTransitions.push_back(newTransition);
            }
    }
    return allTransitions;
};*/