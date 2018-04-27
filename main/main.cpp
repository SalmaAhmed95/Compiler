#include <ctime>
#include "../lexical-analyzer/grammar-parser/Token.hpp"
#include "../lexical-analyzer/grammar-parser/ProductionParser.hpp"
#include "../lexical-analyzer/automata/RegexToNfaConverter.hpp"
#include "../lexical-analyzer/automata/NfaToDfaConverter.h"
#include "../lexical-analyzer/dfa-minimizer/DfaMinimizer.h"
#include "../file-writer/FileWriter.h"
#include "../lexical-analyzer/tokenizer/Tokenizer.h"
#include "../parser/Grammar.h"
#include "../parser/Parser.h"

#define FILES_NUM 6

const std::string DEFAULT_PROPERTIES = "properties.ini";
const std::string DEFAULT_LEXICAL = "lexical_rules.txt";
const std::string DEFAULT_CODE = "code.txt";
const std::string DEFAULT_LEXICAL_OUTPUT = "lexical_output.txt";
const std::string DEFAULT_PARSER_OUTPUT = "parser_output.txt";
const std::string DEFAULT_LEFT_DERIVATION = "left_derivation.txt";
const std::string DEFAULT_CFG_INPUT = "input.txt";

void deleteTokens(std::vector<Token *> v) {
    for (int i = 0; i < v.size(); i++) {
        delete v[i];
    }
}

void getFileNames(int argc, char **argv, std::string &lexicalRules,
                  std::string &properties,
                  std::string &code,
                  std::string &lexicalOutput,
                  std::string &parserOutput,
                  std::string &leftDerivationOutput) {
    if (argc != FILES_NUM + 1) {
        lexicalRules = DEFAULT_LEXICAL;
        properties = DEFAULT_PROPERTIES;
        code = DEFAULT_CODE;
        lexicalOutput = DEFAULT_LEXICAL_OUTPUT;
        parserOutput = DEFAULT_PARSER_OUTPUT;
        leftDerivationOutput = DEFAULT_LEFT_DERIVATION;
    } else {
        lexicalRules = argv[1];
        properties = argv[2];
        code = argv[3];
        lexicalOutput = argv[4];
        parserOutput = argv[5];
        leftDerivationOutput = argv[6];
    }
}

int main(int argc, char **argv) {
    clock_t startTime = clock();

    std::string lexicalRules, code, properties, lexicalOutput, parserOutput, leftDerivationOutput;
    getFileNames(argc, argv, lexicalRules, properties, code,
                 lexicalOutput, parserOutput, leftDerivationOutput);

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

    FileWriter *lexicalWriter = new FileWriter(lexicalOutput);
    FileWriter parserWriter(parserOutput);
    FileWriter leftDerivationWriter(leftDerivationOutput);

    lexicalWriter->writeTransitionTable(dfaMin);
    Tokenizer *tokenizer = new Tokenizer(dfaMin, code, properties, lexicalWriter);

    Grammar grammar;
    ParsingTable *parsingTable = grammar.getGrammarTable(DEFAULT_CFG_INPUT);

    Parser::getInstance().parse(parsingTable, tokenizer, &parserWriter, &leftDerivationWriter);
    std::cout << "Finished Matching & Parsing\n";

    lexicalWriter->closeFile();
    parserWriter.closeFile();
    leftDerivationWriter.closeFile();

    delete nfa;
    delete dfa;
    delete dfaMin;
    delete tokenizer;
    delete lexicalWriter;

    std::cout << (clock() - startTime) * 1.0 / CLOCKS_PER_SEC << '\n';

    return 0;
}
