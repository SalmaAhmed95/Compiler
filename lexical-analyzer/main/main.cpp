#include "../automata/RegexToNfaConverter.hpp"
#include "../grammar-parser/ProductionParser.hpp"
#include "../automata/DFA.h"
#include "../dfa-minimizer/DfaMinimizer.h"

int main() {
/*
//  std::vector<Token *> tokens =
//      ProductionParser::loadLexicalRules("lexical_rules.txt", "properties.ini");
//  // for (int i = 0; i < tokens.size(); i++) {
//  //   std::cout << tokens[i]->getType() << " " << tokens[i]->getPostfixRegix()
//  //             << '\n';
//  // }
//  NFA *nfa = RegexToNfaConverter::getNfa(tokens);
//  nfa->print();
//  std::cout << "HERE" << std::endl;

    DFA *automata = new DFA();
    stateID node1ID = automata->createNode();
    automata->createNode(ACCEPTED, 0, "d");
    automata->createNode(ACCEPTED, 1, "do");
    stateID node3ID = automata->createNode();
    stateID node4ID = automata->createNode();
    stateID node5ID = automata->createNode();
    automata->createNode(ACCEPTED, 2, "double");
    automata->createNode(ACCEPTED, 0, "letter");
    automata->createNode(PHI, 0, "phi");


    automata->addTransition('d', 0, 1);
    automata->addTransition('o', 1, 2);
    automata->addTransition('u', 2, 3);
    automata->addTransition('b', 3, 4);
    automata->addTransition('l', 4, 5);
    automata->addTransition('e', 5, 6);
//    automata->addTransition('f', 0, 7);
//    automata->addTransition('f', 1, 8);
//    automata->addTransition('f', 2, 8);
//    automata->addTransition('f', 3, 8);
//    automata->addTransition('f', 4, 8);
//    automata->addTransition('f', 5, 8);
//    automata->addTransition('f', 6, 8);
//    automata->addTransition('f', 7, 8);
    std::vector<char> alphabets = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                                   'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    for (int i = 0; i < alphabets.size(); i++) {
        if (alphabets[i] == 'd')
            continue;
        automata->addTransition(alphabets[i], 0, 7);
    }
    for (int i = 0; i < alphabets.size(); i++) {
        if (alphabets[i] == 'o')
            continue;
        automata->addTransition(alphabets[i], 1, 8);
    }
    for (int i = 0; i < alphabets.size(); i++) {
        if (alphabets[i] == 'u')
            continue;
        automata->addTransition(alphabets[i], 2, 8);
    }
    for (int i = 0; i < alphabets.size(); i++) {
        if (alphabets[i] == 'b')
            continue;
        automata->addTransition(alphabets[i], 3, 8);
    }
    for (int i = 0; i < alphabets.size(); i++) {
        if (alphabets[i] == 'l')
            continue;
        automata->addTransition(alphabets[i], 4, 8);
    }
    for (int i = 0; i < alphabets.size(); i++) {
        if (alphabets[i] == 'e')
            continue;
        automata->addTransition(alphabets[i], 5, 8);
    }
    for (int i = 0; i < alphabets.size(); i++) {
        automata->addTransition(alphabets[i], 6, 8);
    }
    for (int i = 0; i < alphabets.size(); i++) {
        automata->addTransition(alphabets[i], 7, 8);
    }

    //automata->print();

    PatternMatcher *matcher = new PatternMatcher(automata, "patternTest.txt");
    matcher->analyzeCode();
*/
    DFA automata, minimizedDfa;
    automata.createNode(StateType::ACCEPTED, 0, "a"); //0
    automata.createNode(StateType::INTERMEDIATE, 1, "b"); //1
    automata.createNode(StateType::ACCEPTED, 2, "c"); //2
    automata.createNode(StateType::INTERMEDIATE, 3, "d"); //3
    automata.createNode(StateType::PHI, 4, "e"); //4
    automata.createNode(StateType::INTERMEDIATE, 5, "f"); //5

    automata.addTransition('0', 0, 1);
    automata.addTransition('0', 1, 4);
    automata.addTransition('0', 2, 1);
    automata.addTransition('0', 3, 0);
    automata.addTransition('0', 4, 4);
    automata.addTransition('0', 5, 2);
    automata.addTransition('1', 0, 3);
    automata.addTransition('1', 1, 2);
    automata.addTransition('1', 2, 5);
    automata.addTransition('1', 3, 4);
    automata.addTransition('1', 4, 4);
    automata.addTransition('1', 5, 4);

    minimizedDfa = minimizeDfa(automata);
    for (int i = 0; i < minimizedDfa.getNumberOfStates(); i++) {
        std::cout << i << "-";
        if (minimizedDfa.isAccepted(i)) std::cout << "ACCEPTED";
        if (minimizedDfa.isPHI(i)) std::cout << "PHI";
        std::cout << " | ";
        for (auto transEdge: minimizedDfa.getTransitions(i)) {
            std::cout << "[" << transEdge.transition << ", (";
            for (int j = 0; j < transEdge.nextStates.size(); j++) {
                std::cout << transEdge.nextStates[j] << "-";
                if (minimizedDfa.isAccepted(transEdge.nextStates[j])) std::cout << "ACCEPTED";
                if (minimizedDfa.isPHI(transEdge.nextStates[j])) std::cout << "PHI";
                if (j < transEdge.nextStates.size() - 1) {
                    std::cout << ", ";
                } else {
                    std::cout << ")";
                }
            }
            std::cout << "] ";
        }
        std::cout << std::endl;
    }
    return 0;
}

