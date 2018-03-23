//
// Created by mahmoud on 3/16/18.
//

#include "../automata/Automata.h"
#include "../automata/DFA.h"

#ifndef COMPILER_DFAMINIMIZER_H
#define COMPILER_DFAMINIMIZER_H

class DfaMinimizer {
public:

    static DfaMinimizer &getInstance();

    /**
    * @param dfaGraph a pointer to the DFA automata to be minimized
    * @return a pointer to the minimized DFA automata
    * Memory may need to be freed after done using the returned minimized DFA Object
    */
    DFA *minimizeDfa(DFA *dfaGraph);

    DfaMinimizer(DfaMinimizer const &) = delete;

    void operator=(DfaMinimizer const &) = delete;

private:

    DfaMinimizer() {}

    /**
     * A Map that keeps tracking of which set contains a specific stateID
     */
    std::map<stateID, int> *stateToSetId;

    void initSets(DFA *dfaGraph, std::vector<std::set<stateID>> *sets);

    void partition(std::set<stateID> *setToBePartitioned,
                   std::vector<std::set<stateID >> *next,
                   DFA *dfaGraph);

    void updateStateToSetIdMap(std::set<stateID> *set, int index);

    /**
     * @param state1 the stateID of the first state to compare
     * @param state2 the stateID of the second state to compare
     * @param dfaGraph a pointer to the DFA Graph to be minimized
     * @Return true if two states are equivalent else return false
     * Two states are equivalent if for all possible transitions the next state
     * of state1 and the next state of state2 belong to the same set.
     */
    bool areEquivalentStates(stateID state1, stateID state2, DFA *dfaGraph);

    DFA *buildMinimizedDfa(std::vector<std::set<stateID>> *sets,
                           DFA *dfaGraph);

    void initMinimizedDfa(std::vector<std::set<stateID>> *sets,
                          DFA *dfaGraph,
                          DFA *minimizedDfa);
};

#endif // COMPILER_DFAMINIMIZER_H
