//
// Created by mahmoud on 3/16/18.
//

#include "DfaMinimizer.h"


std::map<stateID, int> *stateToSetId;

void init(DFA *dfaGraph, std::vector<std::set<stateID>> *sets);

void partition(std::set<stateID> *setToBePartitioned,
               std::vector<std::set<stateID >> *next,
               DFA *dfaGraph);

void updateStateToSetIdMap(std::set<stateID> *sets, int index);

bool areEquivalentStates(stateID a, stateID b, DFA *dfaGraph);

Automata *createMinimizedDfa(std::vector<std::set<stateID>> *sets, Automata *dfaGraph);

Automata *minimizeDfa(DFA dfaGraph) {
    std::vector<std::set<stateID>> sets1;
    std::vector<std::set<stateID>> sets2;
    std::vector<std::set<stateID >> *prev = &sets1;
    std::vector<std::set<stateID>> *next = &sets2;
    stateToSetId = new std::map<stateID, int>();

    init(&dfaGraph, &sets1);

    do {
        for (std::set<stateID> set: *prev) {
            partition(&set, next, &dfaGraph);
        }
        for (int setIndex = 0; setIndex < next->size(); setIndex++) {
            updateStateToSetIdMap(&(next->at(setIndex)), setIndex);
        }

        //swap pointers to update the prev for the next partitioning.
        std::vector<std::set<stateID >> *tmp = prev;
        prev = next;
        next = tmp;

    } while (prev->size() != next->size());
    Automata *minimizedDfa = createMinimizedDfa(prev, &dfaGraph);
    delete (stateToSetId);
    return minimizedDfa;
}

void init(DFA *dfaGraph, std::vector<std::set<stateID>> *sets) {
    sets->resize(1);

    //initial sets
    for (stateID i = 0; i < dfaGraph->getNumberOfStates(); i++) {
        if (dfaGraph->isAcceptance(i)) {
            sets->push_back(std::set<stateID>());
            sets->back().insert(i);
        } else {
            sets->front().insert(i);
        }
    }
    for (int i = 0; i < sets->size(); i++) {
        updateStateToSetIdMap(&(sets->at(i)), i);
    }
}

void partition(std::set<stateID> *setToBePartitioned,
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

void updateStateToSetIdMap(std::set<stateID> *set, int index) {
    for (stateID state: *set) {
        stateToSetId->insert(std::pair<stateID, int>(state, index));
    }
}

bool areEquivalentStates(const stateID a, const stateID b, DFA *dfaGraph) {
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

Automata *createMinimizedDfa(std::vector<std::set<stateID>> *sets, Automata *dfaGraph) {
    DFA *minimizedDfa = new DFA();

    // create nodes with acceptance values
    for (int i = 0; i < sets->size(); i++) {
        minimizedDfa->createNode();
        if (dfaGraph->isAcceptance(*sets->at(i).begin())) {
            minimizedDfa->setAcceptance(i, true);
        }
    }

    // get index of the set containing the root
    int rootSetIndex;
    for (int i = 0; i < sets->size(); i++) {
        if (sets->at(i).count(dfaGraph->getRootID())) {
            rootSetIndex = i;
            break;
        }
    }

    // swap the root set with the set at index 0
    iter_swap(sets->begin() + dfaGraph->getRootID(), sets->begin() + rootSetIndex);

    // update the map for the elements at index 0;
    updateStateToSetIdMap(&(sets->at(dfaGraph->getRootID())), dfaGraph->getRootID());

    // update the map for the elements at the prev root index
    updateStateToSetIdMap(&(sets->at(rootSetIndex)), rootSetIndex);

    //Build the minimized DFA
    for (stateID from = 0; from < sets->size(); from) {
        for (char attribute: dfaGraph->getAllAttributes()) {
            stateID oldFrom = *(sets->at(from).begin());
            stateID oldTo = dfaGraph->getTransitions(oldFrom, attribute).front();
            stateID to = (*stateToSetId->find(oldTo)).second;
            Edge edge = Edge(from, to, attribute);
            minimizedDfa->addTransition(&edge);
        }
    }
    return minimizedDfa;
}
