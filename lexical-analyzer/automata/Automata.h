//
// Created by karfass on 15/03/18.
//

#ifndef COMPLIER_AUTOMATA_H
#define COMPLIER_AUTOMATA_H

#include "Node.h"
#include <iostream>
#include <set>

#define ROOT_ID 0

class Automata {

public:
  Automata();

  virtual stateID createNode() = 0;

  virtual stateID createNode(StateType type, int precendence,
                             std::string identifier) = 0;

  void addTransition(char transition, stateID from, stateID to);

  bool isAccepted(stateID curState);


  bool isPHI(stateID curState);

  int getPrecedence(stateID curState);


  stateID getRootID();

  std::string getTokenClass(stateID curState);

  std::set<char> getAllAttributes();


    StateType getStateType(stateID curState);


  stateID getNumberOfStates();


  std::vector<stateID> getTransitions(stateID curState, char transition);

  std::vector<TransEdges> getTransitions(stateID curState);

  void setStateSpec(stateID nodeId, int precedence, std::string tokenClass,
                    StateType stateType);

  void print();

protected:
  stateID lastNodeID;
  std::vector<Node *> graph;
  std::set<char> attributes;

private:
  void print(stateID nodeID, bool *visited);
};

#endif // COMPLIER_AUTOMATA_H
