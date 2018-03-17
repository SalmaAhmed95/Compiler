//
// Created by karfass on 15/03/18.
//

#ifndef COMPLIER_AUTOMATA_H
#define COMPLIER_AUTOMATA_H

#include "Node.h"
#include <set>

class Automata {

public:
  Automata();

  virtual stateID createNode() = 0;

  void addTransition(char transition, stateID from, stateID to);

  void setAcceptance(stateID id, AcceptanceSpec *acceptanceSpec1);

  AcceptanceSpec *getAcceptance(stateID id);

  stateID getRootID();

  std::set<char> getAllAttributes();

  stateID getNumberOfStates();

  std::vector<stateID> getTransitions(stateID curState, char transition);

  std::vector<TransEdges> getTransitions(stateID curState);

    bool isAcceptance(stateID stateId);

    bool setAcceptance(stateID stateId, bool acceptance);

protected:
  stateID lastNodeID;
  std::vector<Node *> graph;
  std::set<char> attributes;
};
#endif // COMPLIER_AUTOMATA_H
