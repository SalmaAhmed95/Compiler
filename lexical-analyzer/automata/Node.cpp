//
// Created by karfass on 15/03/18.
//
#include "Node.h"

Node::Node() {}

Node::Node(stateID id) {
    Node::ID = id;
    Node::stateSpec.stateType = INTERMEDIATE;
    Node::stateSpec.precedence = 0;
    Node::stateSpec.identiifer = " ";
}

Node::Node(stateID id, StateSpec *spec) {
    Node::ID = id;
    Node::stateSpec.stateType = spec->stateType;
    Node::stateSpec.precedence = spec->precedence;
    int bufferSize = spec->identiifer.length() + 1;
    Node::stateSpec.identiifer = spec->identiifer.substr(0, bufferSize);
}

int Node::getPrecendence() {
    return stateSpec.precedence;
}


std::string Node::getIdentifier() {

    return std::string(Node::stateSpec.identiifer);
}


bool Node::isAccepted() {
    return stateSpec.stateType == ACCEPTED;
}

bool Node::isPHI() {
    return stateSpec.stateType == PHI;
}