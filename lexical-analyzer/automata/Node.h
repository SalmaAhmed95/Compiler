//
// Created by karfass on 14/03/18.
//

#ifndef COMPLIER_NODE_H
#define COMPLIER_NODE_H

#include <map>
#include <set>
#include <string>
#include <vector>

typedef int stateID;

struct Edge {
  stateID from;
  stateID to;
  char transition;
};

struct AcceptanceSpec {
  int precedence;
  std::string type;
};

struct TransEdges {
  char transition;
  std::vector<stateID> nextStates;
};

struct TransEdgesDfa {
  char transition;
  int nextState;
};

class Node {

public:
  Node();

  void setAcceptanceState(AcceptanceSpec *spec);
  AcceptanceSpec *getAcceptance();

  virtual void addTransition(stateID node_to, char transition) = 0;
  virtual std::vector<stateID> getTransitions(char transition) = 0;
  virtual std::vector<TransEdges> getTransitions() = 0;

protected:
  stateID ID;
  bool acceptanceState;
  AcceptanceSpec *spec;
  Node(stateID id);
};

#endif // COMPLIER_NODE_H
