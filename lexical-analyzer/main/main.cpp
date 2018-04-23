#include <ctime>
#include "../../parser/CFGParser.h"
#include "../../parser/Grammar.h"
//#include "../../parser/Parser.h"
#include "../automata/DFA.h"
#include "../automata/NfaToDfaConverter.h"
#include "../automata/RegexToNfaConverter.hpp"
#include "../dfa-minimizer/DfaMinimizer.h"
#include "../grammar-parser/ProductionParser.hpp"
#include "../tokenizer/Tokenizer.h"
#include "../../parser/Parser.h"

#define FILES_NUM 5

const std::string DEFAULT_PROPERTIES = "properties.ini";
const std::string DEFAULT_LEXICAL = "lexical_rules.txt";
const std::string DEFAULT_CODE = "code.txt";
const std::string DEFAULT_LEXICAL_OUTPUT = "lexical_output.txt";
const std::string DEFAULT_PARSER_OUTPUT = "parser_output";

void deleteTokens(std::vector<Token *> v) {
    for (int i = 0; i < v.size(); i++) {
        delete v[i];
    }
}

void getFileNames(int argc, char **argv, std::string &lexicalRules,
                  std::string &properties,
                  std::string &code,
                  std::string &lexicalOutput,
                  std::string &parserOutput) {
    if (argc != FILES_NUM + 1) {
        lexicalRules = DEFAULT_LEXICAL;
        properties = DEFAULT_PROPERTIES;
        code = DEFAULT_CODE;
        lexicalOutput = DEFAULT_LEXICAL_OUTPUT;
        parserOutput = DEFAULT_PARSER_OUTPUT;
    } else {
        lexicalRules = argv[1];
        properties = argv[2];
        code = argv[3];
        lexicalOutput = argv[4];
        parserOutput = argv[5];
    }
}

int main(int argc, char **argv) {
    clock_t startTime = clock();
    std::string lexicalRules, code, properties, lexicalOutput, parserOutput;
    getFileNames(argc, argv, lexicalRules, properties, code, lexicalOutput, parserOutput);
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
    // TODO call non default constructor if main has paramters for lexicalOutput file
    // else default constructor
    FileWriter *writer = new FileWriter(lexicalOutput);
    writer->writeTransitionTable(dfaMin);

    FileWriter parserWriter = FileWriter(parserOutput);
    Grammar grammar;
    ParsingTable *parsingTable = grammar.getGrammarTable("input.txt");


    std::cout << "==========================================" << std::endl;
    Tokenizer *tokenizer = new Tokenizer(dfaMin, code, properties, writer);
    Parser::getInstance().initialize(parsingTable);
    ParseResult result(true);
    std::string token;
    while (tokenizer->hasTokens()) {
        if (result.tokenDone) {
            token = tokenizer->nextToken();
        }
        if (tokenizer->tokenFound()) {
            Symbol symbol;
            symbol.name = token;
            result = Parser::getInstance().parse(symbol);
            parserWriter.writeParserResult(result);
        }
    }

    while (!Parser::getInstance().isDone()) {
        Symbol endSymbol = Symbol(END, START);
        result = Parser::getInstance().parse(endSymbol);
        parserWriter.writeParserResult(result);
    }

    writer->closeFile();
    std::cout << "Finished Matching\n";
    delete nfa;
    delete dfa;
    delete dfaMin;
    //delete tokenizer;
    delete writer;
    std::cout << (clock() - startTime) * 1.0 / CLOCKS_PER_SEC << '\n';

//  Grammar grammar;
//  grammar.getGrammarTable("input.txt");

//
//    std::map<Symbol, std::vector<Production>> result = CFGParser::getCFGRules("Inputfile3.txt", "properties.ini");
//
//    std::map<Symbol, std::vector<Production>>::iterator it;
//    for (it = result.begin(); it != result.end(); it++) {
//        std::cout << "NonTerminal name #" << it->first.name << "# type " << it->first.type << "\n";
//        std::vector<Production> rules = it->second;
//        for (Production production : it->second) {
//            production.print();
//        }
//    }

    return 0;
}
