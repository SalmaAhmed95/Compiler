//
// Created by mahmoud on 3/16/18.
//

#include "DfaMinimizer.h"


std::map<stateID, int> *stateToSetId;

void initSets(DFA *dfaGraph, std::vector<std::set<stateID>> *sets);

void partition(std::set<stateID> *setToBePartitioned,
               std::vector<std::set<stateID >> *next,
               DFA *dfaGraph);

void updateStateToSetIdMap(std::set<stateID> *set, int index);

bool areEquivalentStates(stateID a, stateID b, DFA *dfaGraph);

DFA *buildMinimizedDfa(std::vector<std::set<stateID>> *sets, DFA *dfaGraph);

void initMinimizedDfa(std::vector<std::set<stateID>> *sets, DFA *dfaGraph, DFA *minimizedDfa);


void printSets(std::vector<std::set<stateID>> *sets);

DFA *minimizeDfa(DFA *dfaGraph) {
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

void initSets(DFA *dfaGraph, std::vector<std::set<stateID>> *sets) {
    sets->resize(1);
    std::map<std::string, std::set<stateID>> tokensToAccepted;
    //initial sets
    for (stateID i = 0; i < dfaGraph->getNumberOfStates(); i++) {
        if (dfaGraph->isAccepted(i)) {
            tokensToAccepted[dfaGraph->getTokenClass(i)].insert(i);
        } else {
            sets->front().insert(i);
        }
    }
    for (auto it :tokensToAccepted) {
        sets->push_back(std::set<stateID>());
        for (stateID state: it.second) {
            sets->back().insert(state);
        }
    }
    if (sets->front().empty()) {
        sets->erase(sets->begin());
    }
    for (unsigned int i = 0; i < sets->size(); i++) {
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
        stateToSetId->operator[](state) = index;
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

DFA *buildMinimizedDfa(std::vector<std::set<stateID>> *sets, DFA *dfaGraph) {
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

   /* for (int i = 0; i < minimizedDfa->getNumberOfStates();i++) {
        std::cout << i << "("<<minimizedDfa->getTokenClass(i)<<")" << " --->";
        for (char att: minimizedDfa->getAllAttributes()) {
            std::cout << "(" << att << ", " << minimizedDfa->getTransitions(i,att)[0] << ") ";
        }
        std::cout<<std::endl;
    }*/


    return minimizedDfa;
}

void initMinimizedDfa(std::vector<std::set<stateID>> *sets, DFA *dfaGraph, DFA *minimizedDfa) {
    //Create States to represent the sets
    for (unsigned int i = 0; i < sets->size(); i++) {
        stateID stateInSet = *(sets->at(i).begin());
        minimizedDfa->createNode(dfaGraph->getStateType(stateInSet),
                                 dfaGraph->getPrecedence(stateInSet),
                                 dfaGraph->getTokenClass(stateInSet));
    }

    // get index of the set containing the root
    int rootSetIndex = 0;
    for (unsigned int i = 0; i < sets->size(); i++) {
        if (sets->at(i).count(dfaGraph->getRootID())) {
            rootSetIndex = i;
            break;
        }
    }

    // swap the root set with the set at index 0
    iter_swap(sets->begin() + dfaGraph->getRootID(), sets->begin() + rootSetIndex);

    // update the map for the elements at index dfaGraph->getRootID();
    updateStateToSetIdMap(&(sets->at(dfaGraph->getRootID())), dfaGraph->getRootID());

    // update the map for the elements at the prev root index
    updateStateToSetIdMap(&(sets->at(rootSetIndex)), rootSetIndex);
}

void printSets(std::vector<std::set<stateID>> *sets) {
    for (auto set: *sets) {
        for (stateID stateId: set) {
            std::cout << stateId << " ";
        }
        std::cout << std::endl;
    }
}
