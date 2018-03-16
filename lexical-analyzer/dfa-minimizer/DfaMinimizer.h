//
// Created by mahmoud on 3/16/18.
//

#include "../automata/Automata.h"
#include "../automata/DFA.h"

#ifndef COMPILER_DFAMINIMIZER_H
#define COMPILER_DFAMINIMIZER_H

/**
 * @param dfaGraph the DFA automata to be minimized
 * @return a minimized DFA automata
 */
Automata *minimizeDfa(DFA dfaGraph);

#endif //COMPILER_DFAMINIMIZER_H
