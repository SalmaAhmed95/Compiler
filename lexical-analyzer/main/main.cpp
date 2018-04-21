#include "../../parser/CFGParser.h"
#include "../../parser/Grammar.h"
#include "../../parser/Parser.h"
#include "../automata/DFA.h"
#include "../automata/NfaToDfaConverter.h"
#include "../automata/RegexToNfaConverter.hpp"
#include "../dfa-minimizer/DfaMinimizer.h"
#include "../grammar-parser/ProductionParser.hpp"
#include "../tokenizer/Tokenizer.h"

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
  clock_t startTime = clock();
  std::string lexicalRules, code, properties, output;
  getFileNames(argc, argv, lexicalRules, properties, code, output);
  std::vector<Token *> tokens =
      ProductionParser::loadLexicalRules(lexicalRules, properties);
  NFA *nfa = RegexToNfaConverter::getNfa(tokens);
  std::cout << "NFA nodes = " << nfa->getNumberOfStates() << '\n';
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

  ParsingTable parsingTable; //TODO Build the parsing table.
  Parser::getInstance().initialize(&parsingTable);
  Tokenizer *tokenizer = new Tokenizer(dfaMin, code, properties, writer);
    while(tokenizer->hasTokens()){
        std::string token =  tokenizer->nextToken();
        if(tokenizer->tokenFound()) {
          Symbol symbol;
          symbol.name = token;
          std::pair<Production, std::string>* result = Parser::getInstance().parse(&symbol);
          //TODO print result
        }
    }

  writer->closeFile();
  std::cout << "Finished Matching\n";
  delete nfa;
  delete dfa;
  delete dfaMin;
  delete tokenizer;
  delete writer;
  std::cout << (clock() - startTime) * 1.0 / CLOCKS_PER_SEC << '\n';

  Grammar grammar;
    grammar.getGrammarTable("");

 /*  std::map <Symbol, std::vector<Production>> result = CFGParser::getCFGRules("Inputfile.txt","properties.ini");

   std::map <Symbol, std::vector<Production>> :: iterator it;
   for (it = result.begin(); it != result.end(); it++) {
     std::cout<<"NonTerminal name "<<it->first.name<<" type "<<it->first.type<<"\n";
     std::vector<Production> rules = it->second;
     for (Production production : it->second) {
       production.print();
     }
   }

    return 0;*/
}
