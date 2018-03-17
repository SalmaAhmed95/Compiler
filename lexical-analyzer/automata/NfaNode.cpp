//
// Created by karfass on 15/03/18.
//

#include "NfaNode.h"
#include <iostream>

NfaNode::NfaNode(stateID id) : Node(id) {}

NfaNode::NfaNode(stateID id, StateSpec* stateSpec) : Node(id, stateSpec){}

void NfaNode::addTransition(stateID node_to, char transition) {
  transitions.insert(std::pair<char, stateID>(transition, node_to));
}

std::vector<stateID> NfaNode::getTransitions(char transition) {
  std::vector<stateID> nextstates;
  std::pair<std::multimap<char, stateID>::iterator,
            std::multimap<char, stateID>::iterator>
      ret;
  ret = transitions.equal_range(transition);
  for (std::multimap<char, int>::iterator it = ret.first; it != ret.second;
       ++it) {
    nextstates.push_back(it->second);
  }
  return nextstates;
}

std::vector<TransEdges> NfaNode::getTransitions() {
  std::vector<TransEdges> allTransitions;
  std::set<char> char_transitions;
  for (std::multimap<char, int>::iterator it = transitions.begin();
       it != transitions.end(); ++it) {
    char charT = (*it).first;
    if (char_transitions.find(charT) == char_transitions.end()) {
      char_transitions.insert(charT);
      TransEdges newTransition;
      newTransition.transition = charT;
      newTransition.nextStates = getTransitions(charT);
      allTransitions.push_back(newTransition);
    }
  }
  return allTransitions;
}
