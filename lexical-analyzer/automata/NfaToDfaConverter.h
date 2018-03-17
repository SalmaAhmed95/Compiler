//
// Created by karfass on 17/03/18.
//

#ifndef COMPILER_NFATODFACONVERTER_H
#define COMPILER_NFATODFACONVERTER_H


#include "DFA.h"
#include "NFA.h"

struct SetOfNfaStates {
    StateType type;
    AcceptanceSpec spec;
    std::set<stateID> states;
};


class NfaToDfaConverter {
    public:
    DFA *getDFA(NFA *nfa);

   private:
    NfaToDfaConverter();
    void constructEpsTransitionTable(std::vector<SetOfNfaStates> *epsTransitions, NFA *nfa);
    void getEpsTransitionsForState(stateID  curState, SetOfNfaStates *stateEpsTransition, NFA *nfa);

};
#endif //COMPILER_NFATODFACONVERTER_H
