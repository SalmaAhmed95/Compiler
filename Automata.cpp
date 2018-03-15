//
// Created by karfass on 15/03/18.
//

#include "Automata.h"

void Automata::addTransition(Edge *edge) {
    int from = edge->from;
    int to = edge->to;
    Node fromNode = graph[from];
    fromNode.addTransition(to, edge->transition);
}