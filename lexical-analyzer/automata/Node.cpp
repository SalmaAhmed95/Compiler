//
// Created by karfass on 15/03/18.
//
#include "Node.h"

Node::Node() {}

Node::Node(stateID id) {
  Node::ID = id;
  Node::acceptanceState = false;
}

void Node::setAcceptanceState(AcceptanceSpec *spec) {
  Node::acceptanceState = true;
  Node::spec = (AcceptanceSpec *)new AcceptanceSpec;
  Node::spec->precedence = spec->precedence;
  int bufferSize = spec->type.length() + 1;
  char buffer[bufferSize];
  spec->type.copy(buffer, bufferSize - 1, 0);
}

AcceptanceSpec *Node::getAcceptance() { return spec; }
