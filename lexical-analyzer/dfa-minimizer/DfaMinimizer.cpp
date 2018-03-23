//
// Created by mahmoud on 3/16/18.
//

#include "DfaMinimizer.h"

DfaMinimizer &DfaMinimizer::getInstance() {
    static DfaMinimizer instance;
    return instance;
}

DFA *DfaMinimizer::minimizeDfa(DFA *dfaGraph) {
    std::vector<std::set<stateID>> sets1;
    std::vector<std::set<stateID>> sets2;
    std::vector<std::set<stateID >> *prev = &sets1;
    std::vector<std::set<stateID>> *next = &sets2;
    stateToSetId = new std::map<stateID, int>();

    initSets(dfaGraph, prev);
    do {
        next->clear();
        for (std::set<stateID> set: *prev) {
            partition(&set, next, dfaGraph);
        }
        for (unsigned int setIndex = 0; setIndex < next->size(); setIndex++) {
            updateStateToSetIdMap(&(next->at(setIndex)), setIndex);
        }
        //swap pointers
        std::vector<std::set<stateID >> *tmp = prev;
        prev = next;
        next = tmp;
    } while (prev->size() != next->size());

    DFA *minimizedDfa = buildMinimizedDfa(prev, dfaGraph);
    delete (stateToSetId);
    return minimizedDfa;
}

void DfaMinimizer::initSets(DFA *dfaGraph, std::vector<std::set<stateID>> *sets) {
    sets->resize(2);
    std::map<std::string, std::set<stateID>> tokensToAccepted;
    //Add non accepted states and group the accepted ones by TokenClass
    for (stateID i = 0; i < dfaGraph->getNumberOfStates(); i++) {
        if (dfaGraph->isAccepted(i)) {
            tokensToAccepted[dfaGraph->getTokenClass(i)].insert(i);
        } else if (dfaGraph->isPHI(i)) {
            sets->back().insert(i);
        } else {
            sets->front().insert(i);
        }
    }

    //Remove the empty sets should it is necessary.
    for (std::vector<std::set<stateID>>::iterator it = sets->begin();
         it != sets->end(); it++) {
        if ((*it).empty()) {
            sets->erase(it);
            it--;
        }
    }

    //Add the accepted Groups
    for (auto it :tokensToAccepted) {
        sets->push_back(std::set<stateID>());
        for (stateID state: it.second) {
            sets->back().insert(state);
        }
    }

    //update the stateToSetId mapping
    for (unsigned int i = 0; i < sets->size(); i++) {
        updateStateToSetIdMap(&(sets->at(i)), i);
    }
}

void DfaMinimizer::partition(std::set<stateID> *setToBePartitioned,
                             std::vector<std::set<stateID >> *next,
                             DFA *dfaGraph) {
    while (!setToBePartitioned->empty()) {
        stateID i = *(setToBePartitioned->begin()); //select first element
        setToBePartitioned->erase(setToBePartitioned->begin()); // delete it from the set
        next->push_back(std::set<stateID>()); //add new set to the next sets
        std::set<stateID> *nextSet = &(next->back());
        nextSet->insert(i); // insert the deleted element to the new set

        /* - Iterate through the rest of elements comparing with the deleted element
         * - If the selected element and the deleted one are equivalent,
         *   delete that element and insert it into the nextSet
         * - Keep that process till you take all the equivalent elements to the nextSet
         * - Break and try creating a new Set from the remaining elements
         */
        std::set<stateID>::iterator j = setToBePartitioned->begin();
        while (j != setToBePartitioned->end()) {
            if (areEquivalentStates(i, *j, dfaGraph)) {
                nextSet->insert(*j);
                j = setToBePartitioned->erase(j);
            } else {
                j++;
            }
        }
    }
}

void DfaMinimizer::updateStateToSetIdMap(std::set<stateID> *set, int index) {
    for (stateID state: *set) {
        stateToSetId->operator[](state) = index;
    }
}

bool DfaMinimizer::areEquivalentStates(const stateID a, const stateID b, DFA *dfaGraph) {
    for (char attribute: dfaGraph->getAllAttributes()) {
        stateID to1 = dfaGraph->getTransitions(a, attribute).front();
        stateID to2 = dfaGraph->getTransitions(b, attribute).front();
        int setOfTo1 = (*(stateToSetId->find(to1))).second;
        int setOfTo2 = (*(stateToSetId->find(to2))).second;
        if (setOfTo1 != setOfTo2) {
            return false;
        }
    }
    return true;
}

DFA *DfaMinimizer::buildMinimizedDfa(std::vector<std::set<stateID>> *sets, DFA *dfaGraph) {
    DFA *minimizedDfa = new DFA();
    initMinimizedDfa(sets, dfaGraph, minimizedDfa);

    //Build the minimized DFA
    for (stateID from = 0; from < sets->size(); from++) {
        for (char attribute: dfaGraph->getAllAttributes()) {
            stateID oldFrom = *(sets->at(from).begin());
            stateID oldTo = dfaGraph->getTransitions(oldFrom, attribute).front();
            stateID to = (*stateToSetId->find(oldTo)).second;
            minimizedDfa->addTransition(attribute, from, to);
        }
    }
    return minimizedDfa;
}

void DfaMinimizer::initMinimizedDfa(std::vector<std::set<stateID>> *sets, DFA *dfaGraph, DFA *minimizedDfa) {
    int rootOldIndex = stateToSetId->operator[](dfaGraph->getRootID());
    int rootNewIndex = 0;

    // swap the root set with the set at index 0
    iter_swap(sets->begin() + rootNewIndex, sets->begin() + rootOldIndex);

    // update the map for the elements at index dfaGraph->getRootID();
    updateStateToSetIdMap(&(sets->at(rootNewIndex)), rootNewIndex);

    // update the map for the elements at the prev root index
    updateStateToSetIdMap(&(sets->at(rootOldIndex)), rootOldIndex);

    //Create States to represent the sets
    for (unsigned int i = 0; i < sets->size(); i++) {
        stateID stateInSet = *(sets->at(i).begin());
        minimizedDfa->createNode(dfaGraph->getStateType(stateInSet),
                                 dfaGraph->getPrecedence(stateInSet),
                                 dfaGraph->getTokenClass(stateInSet));
    }
}

void DfaMinimizer::printSets(std::vector<std::set<stateID>> *sets) {
    for (unsigned int i = 0; i < sets->size(); i++) {
        std::cout << i << "\t";
        for (stateID stateId: sets->at(i)) {
            std::cout << stateId << " ";
        }
        std::cout << std::endl;
    }
}