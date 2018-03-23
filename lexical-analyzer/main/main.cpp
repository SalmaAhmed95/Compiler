#include "../automata/DFA.h"
#include "../automata/NfaToDfaConverter.h"
#include "../automata/RegexToNfaConverter.hpp"
#include "../code-parser/CodeParser.h"
#include "../dfa-minimizer/DfaMinimizer.h"
#include "../grammar-parser/ProductionParser.hpp"
#include "../pattern-matcher/PatternMatcher.h"

#define FILES_NUM 4

const std::string DEFAULT_PROPERTIES = "properties.ini";
const std::string DEFAULT_LEXICAL = "lexical_rules.txt";
const std::string DEFAULT_CODE = "code.txt";

void deleteTokens(std::vector<Token *> v) {
  for (int i = 0; i < v.size(); i++) {
    delete v[i];
  }
}

void getFileNames(int argc, char **argv, std::string &lexicalRules,
                  std::string &properties, std::string &code,
                  std::string &output) {
  if (argc != FILES_NUM + 1) {
    lexicalRules = DEFAULT_LEXICAL;
    properties = DEFAULT_PROPERTIES;
    code = DEFAULT_CODE;
    output = DEFAULT_OUTPUT;
  } else {
    lexicalRules = argv[1];
    properties = argv[2];
    code = argv[3];
    output = argv[4];
  }
}

int main(int argc, char **argv) {
  std::string lexicalRules, code, properties, output;
  getFileNames(argc, argv, lexicalRules, properties, code, output);
  std::vector<Token *> tokens =
      ProductionParser::loadLexicalRules(lexicalRules, properties);
  NFA *nfa = RegexToNfaConverter::getNfa(tokens);
  deleteTokens(tokens);
  std::cout << "Finished NFA" << std::endl;
  DFA *dfa = NfaToDfaConverter::getDFA(nfa);
  std::cout << "Finished DFA \n";
  DFA *dfaMin = DfaMinimizer::getInstance().minimizeDfa(dfa);
  std::cout << "Finished Minimization\n";
  // TODO call non default constructor if main has paramters for output file
  // else default constructor
  FileWriter *writer = new FileWriter(output);
  writer->writeTransitionTable(dfaMin);
  PatternMatcher *matcher =
      new PatternMatcher(dfaMin, code, properties, writer);
  matcher->analyzeCode();
  writer->closeFile();
  std::cout << "Finished Matching\n";
  delete nfa;
  delete dfa;
  delete dfaMin;
  delete matcher;
  delete writer;
  return 0;
}
