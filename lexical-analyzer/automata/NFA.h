//
// Created by karfass on 14/03/18.
//

#ifndef COMPLIER_NFA_H
#define COMPLIER_NFA_H

#include<string>
#include <vector>
#include "Automata.h"
#include "NfaNode.h"


class NFA : public Automata {
public:
    stateID createNode();


};

#endif //COMPLIER_NFA_H