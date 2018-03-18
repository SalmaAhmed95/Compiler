#include "../automata/RegexToNfaConverter.hpp"
#include "../grammar-parser/ProductionParser.hpp"
#include "../automata/DFA.h"
#include "../pattern-matcher/PatternMatcher.h"

int main() {

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

}
