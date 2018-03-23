//
// Created by karfass on 15/03/18.
//

#include "DfaNode.h"
#include "Definitions.h"

#include <limits.h>

DfaNode::DfaNode(stateID id) : Node(id) {}

DfaNode::DfaNode(stateID id, StateSpec *stateSpec) : Node(id, stateSpec) {}

void DfaNode::addTransition(stateID node_to, char transition) {
  transitions.insert(std::pair<char, stateID>(transition, node_to));
}

std::vector<TransEdges> DfaNode::getTransitions() {
  std::vector<TransEdges> allTransitions;
  for (std::multimap<char, int>::iterator it = transitions.begin();
       it != transitions.end(); ++it) {
    char charT = (*it).first;
    if (charT != EPS_TRANS) {
      TransEdges newTransition;
      newTransition.transition = charT;
      newTransition.nextStates = getTransitions(charT);
      allTransitions.push_back(newTransition);
    }
  }
  return allTransitions;
}

std::vector<stateID> DfaNode::getTransitions(char transition) {
  std::vector<stateID> nextstates;
  if (transitions.find(transition) != transitions.end())
  nextstates.push_back(transitions.find(transition)->second);

  return nextstates;
}
