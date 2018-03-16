#include <iostream>
#include "Automata.h"
#include "NFA.h"

int main() {
     NFA* automata = new NFA();
    stateID node1ID = automata->createNode();

    stateID node2ID = automata->createNode();
    stateID node3ID = automata->createNode();
    Edge edge;
    edge.from = 0;
    edge.to = 1;
    edge.transition = 'a';
    Edge edge2;
    edge2.from = 0;
    edge2.to = 2;
    edge2.transition = 'a';
    automata->addTransition(&edge);
    automata->addTransition(&edge2);
    //std::vector<stateID > zew = automata->getTransitions(0,'a');
    std::vector<TransEdges> zew = automata->getTransitions(0);
    std::cout<<zew[0].transition<<std::endl;
    for (std::vector<stateID>::iterator it = zew[0].nextStates.begin(); it <zew[0].nextStates.end();++it) {
        std::cout<<*it<<" ";
    }


    return 0;
}