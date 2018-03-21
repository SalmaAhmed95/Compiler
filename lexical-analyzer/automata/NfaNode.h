//
// Created by karfass on 15/03/18.
//

#ifndef COMPLIER_NFANODE_H
#define COMPLIER_NFANODE_H

#include "Node.h"

class NfaNode : public Node {

public:
  NfaNode(stateID id, int minAsciiCodeValue, int maxAsciiCoedValue);
  NfaNode(stateID id, StateSpec *stateSpec,int minAsciiCodeValue, int maxAsciiCoedValue);
  void addTransition(stateID node_to, char transition);

  std::vector<TransEdges> getTransitions();

  std::vector<stateID> getTransitions(char transition);

private:
  std::vector<std::vector<stateID> > transitions;
    int offsetCharIndex;
    int charRange;
};
#endif // COMPLIER_NFANODE_H
