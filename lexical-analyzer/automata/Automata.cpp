//
// Created by karfass on 15/03/18.
//

#include "Automata.h"
#include "Node.h"

Automata::Automata() : lastNodeID(0) {}

void Automata::addTransition(char transition, stateID from, stateID to) {
  Node *fromNode = graph[from];
  fromNode->addTransition(to, transition);
  attributes.insert(transition);
}

bool Automata::isAccepted(stateID curState) {
  Node *curNode = graph[curState];
  return curNode->isAccepted();
}

bool Automata::isPHI(stateID curState) {
  Node *curNode = graph[curState];
  return curNode->isPHI();
}

int Automata::getPrecedence(stateID curState) {
  Node *curNode = graph[curState];
  return curNode->getPrecedence();
}

std::string Automata::getTokenClass(stateID curState) {
  Node *curNode = graph[curState];
  return curNode->getTokenClass();
}

StateType Automata::getStateType(stateID curState) {
  Node *curNode = graph[curState];
  return curNode->getStateType();
}

stateID Automata::getRootID() { return ROOT_ID; }

std::set<char> Automata::getAllAttributes() { return attributes; }

stateID Automata::getNumberOfStates() { return lastNodeID; }

std::vector<stateID> Automata::getTransitions(stateID curState,
                                              char transition) {
  Node *curNode = graph[curState];
  return curNode->getTransitions(transition);
}

std::vector<TransEdges> Automata::getTransitions(stateID curState) {
  Node *curNode = graph[curState];
  return curNode->getTransitions();
}

void Automata::setStateSpec(stateID nodeId, int precedence,
                            std::string tokenClass, StateType stateType) {
  Node *node = graph[nodeId];
  node->setStateSpec(precedence, tokenClass, stateType);
}

void Automata::print() {
  stateID nodeID = getRootID();
  bool *visited = new bool[(int)getNumberOfStates()];
  for (int i = 0; i < (int)getNumberOfStates(); i++) {
    visited[i] = false;
  }
  print(nodeID, visited);
  delete[] visited;
}

void Automata::print(stateID nodeID, bool *visited) {
  visited[nodeID] = true;
  std::vector<TransEdges> edges = getTransitions(nodeID);
  if ((int)edges.size() == 0) {
    return;
  }
  for (int i = 0; i < edges.size(); i++) {
    char trans = edges[i].transition;
    for (int j = 0; j < edges[i].nextStates.size(); j++) {
      stateID to = edges[i].nextStates[j];
      std::cout << "going form " << nodeID << " to " << to << " by " << trans
                << '\n';
      if (!visited[to]) {
        print(to, visited);
      }
    }
  }
}
