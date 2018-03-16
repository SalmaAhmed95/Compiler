#include "../grammar-parser/ProductionParser.hpp"

int main() {

  ProductionParser::loadLexicalRules("lexical_rules.txt", "properties.ini");
  std::cout << "HERE" << std::endl;
}
