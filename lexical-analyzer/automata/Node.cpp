//
// Created by karfass on 15/03/18.
//
#include "Node.h"

Node::Node() {}

Node::Node(stateID id) {
    Node::ID = id;
    Node::stateSpec.stateType = INTERMEDIATE;
    Node::stateSpec.precedence = 0;
    Node::stateSpec.identifier = " ";
}

Node::Node(stateID id, StateSpec *spec) {
    Node::ID = id;
    Node::stateSpec.stateType = spec->stateType;
    Node::stateSpec.precedence = spec->precedence;
    int bufferSize = spec->identifier.length() + 1;
    Node::stateSpec.identifier = spec->identifier.substr(0, bufferSize);
}

int Node::getPrecedence() {
    return stateSpec.precedence;
}


std::string Node::getIdentifier() {

    return std::string(Node::stateSpec.identifier);
}


bool Node::isAccepted() {
    return stateSpec.stateType == ACCEPTED;
}

bool Node::isPHI() {
    return stateSpec.stateType == PHI;
}