//
// Created by karfass on 17/03/18.
//
#include "NfaToDfaConverter.h"
#include <queue>

#include "Definitions.h"

DFA *NfaToDfaConverter::getDFA(NFA *nfa) {
    DFA *dfa = new DFA();
    std::vector<SetOfNfaStates> epsTable;
    std::queue<NfaStatesToDfa> queueDfaStates;
    std::map<SetOfNfaStates, stateID> mapDfaStates;
    epsTable = constructEpsTransitionTable(nfa);
    std::vector<SetOfNfaStates>::iterator it;
    /*pushing start closure and creating the start node for the dfa*/
    int nfaRootID = nfa->getRootID();
    StateSpec startClosure = epsTable[nfa->getRootID()].stateSpec;
    dfa->createNode(startClosure.stateType, startClosure.precedence,
                    startClosure.tokenClass);
    NfaStatesToDfa root(dfa->getRootID(), epsTable[nfa->getRootID()].states);
    mapDfaStates.insert(std::pair<SetOfNfaStates, stateID>(
            epsTable[nfa->getRootID()], dfa->getRootID()));
    queueDfaStates.push(root);
    /*main loop*/
    int i = 0;
    //    std::cout << "finished construction\n";
    while (!queueDfaStates.empty()) {
        NfaStatesToDfa curNode = queueDfaStates.front();
        int curNodeID = curNode.dfaID;
        queueDfaStates.pop();
        int charIndex = 0;
        for (auto transition : nfa->getAllAttributes()) {
            if (transition != EPS_TRANS) {
                SetOfNfaStates newStates;
                getNextState(&newStates, &curNode.nfaStates, &epsTable,
                              transition, nfa);

                int nextNodeID;
                std::map<SetOfNfaStates, stateID>::iterator nextDfaState =
                        mapDfaStates.find(newStates);
                if (nextDfaState == mapDfaStates.end()) {
                    nextNodeID = dfa->createNode(newStates.stateSpec.stateType,
                                                 newStates.stateSpec.precedence,
                                                 newStates.stateSpec.tokenClass);
                    mapDfaStates.insert(
                            std::pair<SetOfNfaStates, stateID>(newStates, nextNodeID));
                    NfaStatesToDfa newState(nextNodeID, newStates.states);
                    queueDfaStates.push(newState);

                } else {
                    nextNodeID = nextDfaState->second;
                }
                dfa->addTransition(transition, curNodeID, nextNodeID);
            }
            charIndex++;
        }
    }
    return dfa;
}

void NfaToDfaConverter::getNextState(
        SetOfNfaStates *nextStates, std::set<stateID> *curNfaStates,
        std::vector<SetOfNfaStates> *epsTable, char transition, NFA *nfa) {
    /*iterating over current nfa states to get next transitions*/
    for (auto nfaState : *curNfaStates) {
        std::vector<stateID> nextNfaStates =
                nfa->getTransitions(nfaState, transition);
        /*iterating over next nfa states to get their epsilon transitions
     * transitions*/
        for (auto nextNfaState : nextNfaStates) {
            /*iterating over the epsilon transitions*/
            for (auto nfaNextStateEps : (*epsTable)[nextNfaState].states) {
                nextStates->states.insert(nfaNextStateEps);
                updateSetOfNfaStatesSpec(&nextStates->stateSpec,
                                         nfa->getStateType(nfaNextStateEps),
                                         nfa->getPrecedence(nfaNextStateEps),
                                         nfa->getTokenClass(nfaNextStateEps));
            }
        }
    }
    if (nextStates->states.empty()) {
        nextStates->stateSpec.stateType = PHI;
    }
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

void NfaToDfaConverter::getEpsTransitionsForState(
        stateID curState, std::vector<SetOfNfaStates> *epsTable, NFA *nfa) {
    (*epsTable)[curState].states.insert(curState);
    SetOfNfaStates *curSetOfNfaStates = &(*epsTable)[curState];
    updateSetOfNfaStatesSpec(
            &curSetOfNfaStates->stateSpec, nfa->getStateType(curState),
            nfa->getPrecedence(curState), nfa->getTokenClass(curState));

    std::vector<stateID> epsTransitions =
            nfa->getTransitions(curState, EPS_TRANS);
    for (auto nextState : epsTransitions) {
        curSetOfNfaStates->states.insert(nextState);
        updateSetOfNfaStatesSpec(
                &curSetOfNfaStates->stateSpec, nfa->getStateType(nextState),
                nfa->getPrecedence(nextState), nfa->getTokenClass(nextState));
        if ((*epsTable)[nextState].states.size() == 0) {
            getEpsTransitionsForState(nextState, epsTable, nfa);
        }

        for (auto recuNextState : (*epsTable)[nextState].states) {
            curSetOfNfaStates->states.insert(recuNextState);
            updateSetOfNfaStatesSpec(
                    &curSetOfNfaStates->stateSpec, nfa->getStateType(recuNextState),
                    nfa->getPrecedence(recuNextState), nfa->getTokenClass(recuNextState));
        }
    }
}

void NfaToDfaConverter::updateSetOfNfaStatesSpec(StateSpec *mainState,
                                                 StateType nextType,
                                                 int nextPrecedence,
                                                 std::string nextTokenClass) {
    if (nextType == ACCEPTED) {
        if (mainState->stateType == INTERMEDIATE) {
            mainState->tokenClass.assign(nextTokenClass);
            mainState->precedence = nextPrecedence;
        }
        mainState->stateType = ACCEPTED;
        if (nextPrecedence > mainState->precedence) {
            mainState->precedence = nextPrecedence;
            mainState->tokenClass.assign(nextTokenClass);
        }
    }
}
