//
// Created by karfass on 15/03/18.
//
#include "Node.h"

Node::Node() {}

Node::Node(stateID id) {
  Node::ID = id;
  Node::stateType = INTERMEDIATE;
}

void Node::setAcceptanceState(AcceptanceSpec *spec) {
  Node::stateType = ACCEPTED;
  Node::spec.precedence = spec->precedence;
  int bufferSize = spec->type.length() + 1;
  Node::spec.type = spec->type.substr(0, bufferSize);
}

AcceptanceSpec *Node::getAcceptance() {
  AcceptanceSpec *copySpec = (AcceptanceSpec *)new AcceptanceSpec;
  copySpec->precedence = spec.precedence;
  int bufferSize = spec.type.length() + 1;
  copySpec->type = spec.type.substr(0, bufferSize);
  return copySpec;
}


void Node::setPHIState(){
  Node::stateType = PHI;
}

bool Node::isAccepted(){
  return stateType == ACCEPTED;
}

bool Node::isPHI(){
  return stateType == PHI;
}