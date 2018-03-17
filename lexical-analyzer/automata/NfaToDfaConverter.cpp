//
// Created by karfass on 17/03/18.
//
#include "NfaToDfaConverter.h"
#include <queue>

DFA *NfaToDfaConverter::getDFA(NFA *nfa) {
  DFA *dfa = new DFA();
  std::vector<SetOfNfaStates> epsTransitions;
  std::queue<SetOfNfaStates> newStates;
  constructEpsTransitionTable(&epsTransitions, nfa);
  /*pushing start closure and creating the start node for the dfa*/
  int nfaRootID = nfa->getRootID();
  newStates.push(epsTransitions[nfaRootID]);
  dfa->createNode();
}

void NfaToDfaConverter::constructEpsTransitionTable(
    std::vector<SetOfNfaStates> *epsTransitions, NFA *nfa) {}
