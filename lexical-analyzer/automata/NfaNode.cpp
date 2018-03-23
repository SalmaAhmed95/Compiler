//
// Created by karfass on 15/03/18.
//

#include "NfaNode.h"
#include "Definitions.h"


#include <iostream>

NfaNode::NfaNode(stateID id, int minAsciiCodeValue, int maxAsciiCoedValue)
    : Node(id) {
  NfaNode::offsetCharIndex = minAsciiCodeValue;
  NfaNode::charRange = maxAsciiCoedValue - minAsciiCodeValue + 1;
  NfaNode::transitions.resize(charRange);
}

NfaNode::NfaNode(stateID id, StateSpec *stateSpec, int minAsciiCodeValue,
                 int maxAsciiCoedValue)
    : Node(id, stateSpec) {}

void NfaNode::addTransition(stateID node_to, char transition) {
  transitions[transition - offsetCharIndex].push_back(node_to);
}

std::vector<stateID> NfaNode::getTransitions(char transition) {
  return transitions[transition - offsetCharIndex];
}

std::vector<TransEdges> NfaNode::getTransitions() {
  std::vector<TransEdges> allTransitions;
  for (int i = 0; i < charRange; i++) {
<<<<<<< HEAD
    char charT = (char) (offsetCharIndex + i);
    if (charT != EPS_TRANS) {
      TransEdges newTransition;
      newTransition.transition = charT;
      newTransition.nextStates = getTransitions(charT);
      allTransitions.push_back(newTransition);
    }
=======
    char charT = (char)(offsetCharIndex + i);
    TransEdges newTransition;
    newTransition.transition = charT;
    newTransition.nextStates = getTransitions(charT);
    allTransitions.push_back(newTransition);
>>>>>>> 98e6cab655dd732a3cd303e786ca94b4bc0525d6
  }
  return allTransitions;
}
