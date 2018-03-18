#include "../automata/RegexToNfaConverter.hpp"
#include "../grammar-parser/ProductionParser.hpp"

int main() {

  std::vector<Token *> tokens =
      ProductionParser::loadLexicalRules("lexical_rules.txt", "properties.ini");
  // for (int i = 0; i < tokens.size(); i++) {
  //   std::cout << tokens[i]->getType() << " " << tokens[i]->getPostfixRegix()
  //             << '\n';
  // }
  NFA *nfa = RegexToNfaConverter::getNfa(tokens);
  nfa->print();
  std::cout << "HERE" << std::endl;
}
