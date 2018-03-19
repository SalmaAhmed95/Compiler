//
// Created by karfass on 17/03/18.
//
#include "NfaToDfaConverter.h"
#include <queue>

#define EPS_TRANS '`'

DFA *NfaToDfaConverter::getDFA(NFA *nfa) {
  DFA *dfa = new DFA();
  std::vector<SetOfNfaStates> epsTransitions;
  std::queue<NfaStatesToDfa> queueDfaStates;
  std::map<SetOfNfaStates, stateID> setOfDfaStates;
  epsTransitions = constructEpsTransitionTable(nfa);

  /*pushing start closure and creating the start node for the dfa*/
  int nfaRootID = nfa->getRootID();
  StateSpec startClosure = epsTransitions[nfa->getRootID()].stateSpec;
  dfa->createNode(startClosure.stateType, startClosure.precedence,
                  startClosure.tokenClass);
  NfaStatesToDfa root(dfa->getRootID(),
                      epsTransitions[nfa->getRootID()].states);
  setOfDfaStates.insert(std::pair<SetOfNfaStates, stateID>(
      epsTransitions[nfa->getRootID()], dfa->getRootID()));
  queueDfaStates.push(root);
  /*main loop*/
  while (queueDfaStates.empty()) {
    NfaStatesToDfa temp = queueDfaStates.front();
    int currentNode = temp.dfaID;
    queueDfaStates.pop();
    std::set<char> arrtibutes = nfa->getAllAttributes();
    for (std::set<char>::iterator it = arrtibutes.begin();
         it != arrtibutes.end(); ++it) {
      char transition = *it;
      if (transition != EPS_TRANS) {
        SetOfNfaStates newStates;
        getNextState(&newStates, &temp.nfaStates, &epsTransitions, transition,
                     nfa);
        int nextNodeID = 0;
        std::map<SetOfNfaStates, stateID>::iterator dfaState =
            setOfDfaStates.find(newStates);
        if (dfaState == setOfDfaStates.end()) {
          nextNodeID = dfa->createNode(newStates.stateSpec.stateType,
                                       newStates.stateSpec.precedence,
                                       newStates.stateSpec.tokenClass);
          setOfDfaStates.insert(
              std::pair<SetOfNfaStates, stateID>(newStates, nextNodeID));
          NfaStatesToDfa newState(nextNodeID, newStates.states);
          queueDfaStates.push(newState);

        } else {
          nextNodeID = dfaState->second;
        }
        dfa->addTransition(transition, currentNode, nextNodeID);
      }
    }
  }
  return dfa;
}

std::vector<SetOfNfaStates>
NfaToDfaConverter::constructEpsTransitionTable(NFA *nfa) {
  std::vector<SetOfNfaStates> epsTable(nfa->getNumberOfStates());
  for (int i = 0; i < nfa->getNumberOfStates(); i++) {
    if (epsTable[i].states.size() == 0) {
      getEpsTransitionsForState(i, &epsTable, nfa);
    }
  }
  return epsTable;
}

void NfaToDfaConverter::getNextState(SetOfNfaStates *nextStates,
                                     std::set<stateID> *states,
                                     std::vector<SetOfNfaStates> *epsTable,
                                     char transition, NFA *nfa) {
  std::set<stateID>::iterator nfaState;
  for (nfaState = states->begin(); nfaState != states->end(); ++nfaState) {
    std::vector<stateID> certainTransitions =
        nfa->getTransitions(*nfaState, transition);
    std::vector<stateID>::iterator nfaNextState;
    for (nfaNextState = certainTransitions.begin();
         nfaNextState != certainTransitions.end(); ++nfaNextState) {
      std::set<stateID>::iterator nfaNextStateEps;

      for (nfaNextStateEps = (*epsTable)[*nfaNextState].states.begin();
           nfaNextStateEps != (*epsTable)[*nfaNextState].states.end();
           ++nfaNextStateEps) {
        nextStates->states.insert(*nfaNextStateEps);
        updateSetOfNfaStatesSpec(&nextStates->stateSpec,
                                 nfa->getStateType(*nfaNextStateEps),
                                 nfa->getPrecedence(*nfaNextStateEps),
                                 nfa->getTokenClass(*nfaNextStateEps));
      }
    }
  }
  if (nextStates->states.empty() == 0) {
    nextStates->stateSpec.stateType = PHI;
  }
}

void NfaToDfaConverter::getEpsTransitionsForState(
    stateID curState, std::vector<SetOfNfaStates> *epsTable, NFA *nfa) {
  (*epsTable)[curState].states.insert(curState);
  updateSetOfNfaStatesSpec(
      &(*epsTable)[curState].stateSpec, nfa->getStateType(curState),
      nfa->getPrecedence(curState), nfa->getTokenClass(curState));

  std::vector<stateID> epsTransitions =
      nfa->getTransitions(curState, EPS_TRANS);
  for (auto nextState : epsTransitions) {
    (*epsTable)[curState].states.insert(nextState);
    updateSetOfNfaStatesSpec(
        &(*epsTable)[curState].stateSpec, nfa->getStateType(nextState),
        nfa->getPrecedence(nextState), nfa->getTokenClass(nextState));
    if ((*epsTable)[curState].states.size() == 0) {
      getEpsTransitionsForState(nextState, epsTable, nfa);
    }
    for (auto recuNextState : (*epsTable)[nextState].states) {
      (*epsTable)[curState].states.insert(recuNextState);
      updateSetOfNfaStatesSpec(
          &(*epsTable)[curState].stateSpec, nfa->getStateType(recuNextState),
          nfa->getPrecedence(recuNextState), nfa->getTokenClass(recuNextState));
    }
  }
}

void NfaToDfaConverter::updateSetOfNfaStatesSpec(StateSpec *mainState,
                                                 StateType nextType,
                                                 int nextPrecedence,
                                                 std::string nextTokenClass) {
  if (nextType == ACCEPTED) {
    mainState->stateType = ACCEPTED;
    if (nextPrecedence > mainState->precedence) {
      mainState->precedence = nextPrecedence;
      mainState->tokenClass.assign(nextTokenClass);
    } else {
      if (mainState->stateType == INTERMEDIATE) {
        mainState->tokenClass.assign(nextTokenClass);
      }
    }
  }
}
