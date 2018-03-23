//
// Created by karfass on 23/03/18.
//

#ifndef COMPILER_DEFINITIONS_H
#define COMPILER_DEFINITIONS_H

#define EPS_TRANS '`'
typedef int stateID;

struct TransEdges {
  char transition;
  std::vector<stateID> nextStates;
};

#endif // COMPILER_DEFINITIONS_H
