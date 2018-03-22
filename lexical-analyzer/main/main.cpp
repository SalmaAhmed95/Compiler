#include "../automata/DFA.h"
#include "../automata/NfaToDfaConverter.h"
#include "../automata/RegexToNfaConverter.hpp"
#include "../code-parser/CodeParser.h"
#include "../dfa-minimizer/DfaMinimizer.h"
#include "../grammar-parser/ProductionParser.hpp"


#include "../dfa-minimizer/DfaMinimizer.h"
#include "../automata/NfaToDfaConverter.h"
#include "../pattern-matcher/PatternMatcher.h"

void deleteTokens(std::vector<Token *> v) {
    for(int i = 0; i < v.size(); i++) {
        delete v[i];
    }
}

int main() {
    std::vector<Token *> tokens =
            ProductionParser::loadLexicalRules("lexical_rules.txt", "properties.ini");
    NFA *nfa = RegexToNfaConverter::getNfa(tokens);
    deleteTokens(tokens);
    std::cout << "Finished NFA" << std::endl;
    DFA *dfa = NfaToDfaConverter::getDFA(nfa);
    std::cout<<"Finished DFA \n";
    DFA* dfaMin = minimizeDfa(dfa);
    std::cout<<"Finished Minimization\n";
    //TODO call non default constructor if main has paramters for output file else default constructor
    FileWriter *writer = new FileWriter();
    PatternMatcher *pattern = new PatternMatcher(dfaMin, "code.txt","properties.ini",writer);
    pattern->analyzeCode();
    writer->closeFile();
    std::cout<<"Finished Matching\n";
    delete nfa;
    delete dfa;
    delete dfaMin;
    delete pattern;
    delete writer;
  return 0;
}
