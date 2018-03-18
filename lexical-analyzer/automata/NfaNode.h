//
// Created by karfass on 15/03/18.
//

#ifndef COMPLIER_NFANODE_H
#define COMPLIER_NFANODE_H

#include "Node.h"

class NfaNode : public Node {

public:
  NfaNode(stateID id);
  NfaNode(stateID id, StateSpec *stateSpec);
  void addTransition(stateID node_to, char transition);

  std::vector<TransEdges> getTransitions();

  std::vector<stateID> getTransitions(char transition);

private:
  std::multimap<char, stateID> transitions;
};
#endif // COMPLIER_NFANODE_H
