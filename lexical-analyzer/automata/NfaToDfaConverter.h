//
// Created by karfass on 17/03/18.
//

#ifndef COMPILER_NFATODFACONVERTER_H
#define COMPILER_NFATODFACONVERTER_H

#include "DFA.h"
#include "NFA.h"

struct SetOfNfaStates {

    StateSpec stateSpec;
    std::set<stateID> states;
    bool operator <(const SetOfNfaStates& x) const{
        return states < x.states;
    }
};


struct NfaStatesToDfa {
    stateID dfaID;
    std::set<stateID> nfaStates;
    NfaStatesToDfa(stateID dfaID, std::set<stateID> states) : dfaID(dfaID), nfaStates(states){}
};

class NfaToDfaConverter {

    public:
    static DFA *getDFA(NFA *nfa);

   private:
    NfaToDfaConverter();
    static std::vector<SetOfNfaStates> constructEpsTransitionTable(NFA *nfa);
    static void getEpsTransitionsForState(stateID  curState,std::vector<SetOfNfaStates>* epsTable, NFA *nfa);
    static void getNextState(SetOfNfaStates *nextStates, std::set<stateID> *states, std::vector<SetOfNfaStates>* epsTable,
                      char transition, NFA *nfa);
    static void updateSetOfNfaStatesSpec(StateSpec *mainState, StateType nextType ,int nextPrecedence, std::string nextTokenClass);

};
#endif // COMPILER_NFATODFACONVERTER_H
