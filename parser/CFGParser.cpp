//
// Created by karfass on 18/04/2018.

#include "CFGParser.h"


#include <set>
#include "../lexical-analyzer/utils/StringUtils.h"

#define START_LINE '#'
#define TERMINAL_IDENTIFIER '\''
#define OR_SEPARATOR  '|'


const std::string DEFINITION_SEPARATOR = "::=";

const std::string LAMBDA_SYMBOL = "\\L";


void CFGParser::parseLine(std::string &curRule, std::string &firstSymbolName, std::map<Symbol, std::vector<Production>> *rules) {
    size_t index = StringUtils::getFirstChar(curRule);
    if (index != std::string::npos && curRule.at(index) == START_LINE) {
        curRule = curRule.erase(0, index + 1);
        std::vector<std::string> tokens = StringUtils::splitString(curRule, DEFINITION_SEPARATOR);
       if (tokens.size() != 2) {
            errorRoutine();
        } else {
            std::string nonTerminal = tokens[0];
            Symbol newSymbol(nonTerminal, NON_TERMINAL);
            if (rules->empty()) {
                newSymbol.type = START;
                firstSymbolName = nonTerminal;
            }

            std::vector<Production> productions = calculateProductions(tokens[1],firstSymbolName);
            std::map<Symbol, std::vector<Production>>::iterator it;
            it = rules->find(newSymbol);

            if (it != rules->end()) {
                std::vector<Production> curRules = it->second;
                for (Production production : productions) {
                    curRules.push_back(production);
                }
                rules->erase(it);
                rules->insert(std::pair<Symbol, std::vector<Production>>(newSymbol, curRules));
            } else {
                rules->insert(std::pair<Symbol, std::vector<Production>>(newSymbol, productions));
            }
        }
    } else {
        errorRoutine();
    }
    curRule.clear();
}

std::map<Symbol, std::vector<Production>>
CFGParser::getCFGRules(std::string rulesFileName, std::string propertiesFileName) {
    std::map<Symbol, std::vector<Production>> rules;
    std::ifstream *inFile = openFile(rulesFileName);
    Properties::PropertiesData propertiesData;
    loadProperties(propertiesFileName, propertiesData);
    std::string curRule;
    std::string curLine;
    std::string startSymbolName;
    while (std::getline(*inFile, curLine)) {
        size_t index = StringUtils::getFirstChar(curLine);
        if (index != std::string::npos && curLine.at(index) == START_LINE) {
            if (!curRule.empty()) {
                parseLine(curRule, startSymbolName, &rules);
            }
        }
        curRule.append(curLine);
    }
    if (!curRule.empty()) {
        parseLine(curRule, startSymbolName, &rules);
    }

    if (!checkRulesValidaty(&rules)) {
        errorRoutine();
    }

    performLeftRecusiveElimination(&rules);
    inFile->close();
    return rules;
}

std::ifstream *CFGParser::openFile(std::string fileName) {
    std::ifstream *inFile = new std::ifstream;
    inFile->open(fileName);
    if (!inFile) {
        std::cout << "Unable to find grammer rules file";
        exit(1);
    }
    return inFile;
}


std::vector<Production> CFGParser::calculateProductions(std::string &rhs, std::string &startSymbolName) {
    std::vector<Production> rules;
    std::string curToken;
    bool singleQuoteFound = false;
    bool error = false;
    Production newProduction;
    rules.push_back(newProduction);
    for (std::size_t index = 0; index < rhs.length(); index++) {
        char curChar = rhs.at(index);
        if (StringUtils::isDelimiter(curChar)) {
            if (!singleQuoteFound) {
                if (curToken.length() != 0) {
                    if (curToken == startSymbolName) {
                        Symbol newTerminal(curToken, START);
                        rules.back().production.push_back(newTerminal);
                    } else {
                        Symbol newTerminal(curToken, NON_TERMINAL);
                        rules.back().production.push_back(newTerminal);
                    }
                    curToken.clear();
                 }
            }
        } else if (curChar == TERMINAL_IDENTIFIER && (index == 0 || index > 0 && rhs.at(index - 1) != '\\')) {
            if (!singleQuoteFound) {
                singleQuoteFound = true;
            } else {
                if (curToken.length() != 0) {
                    Symbol newTerminal(curToken, TERMINAL);
                    rules.back().production.push_back(newTerminal);
                    singleQuoteFound = false;
                    curToken.clear();
                }
            }
        } else if (curChar == OR_SEPARATOR && index > 0 && rhs.at(index - 1) != '\\') {
            if (singleQuoteFound) {
                errorRoutine();
            } else {
                if (curToken.length() != 0) {
                    if (curToken == startSymbolName){
                        Symbol newTerminal(curToken, START);
                        rules.back().production.push_back(newTerminal);
                    }
                    Symbol newTerminal(curToken, NON_TERMINAL);
                    rules.back().production.push_back(newTerminal);
                }
                curToken.clear();
            }
            Production newProduction;
            rules.push_back(newProduction);

        } else if (curChar == LAMBDA_SYMBOL.at(1) && index > 0 && rhs.at(index - 1) == LAMBDA_SYMBOL.at(0)) {
            if (curToken.length() > 1 || singleQuoteFound) {
                errorRoutine();
            }
            curToken.append(1, curChar);
            Symbol newTerminal(curToken, EPSILON);
            rules.back().production.push_back(newTerminal);
            curToken.clear();
        } else {
            curToken.append(1, curChar);
        }
    }

    if (singleQuoteFound) {
        errorRoutine();
    } else {
        if (!curToken.empty()) {
            if (curToken == startSymbolName) {
                Symbol newTerminal(curToken, START);
                rules.back().production.push_back(newTerminal);
            } else {
                Symbol newTerminal(curToken, NON_TERMINAL);
                rules.back().production.push_back(newTerminal);
            }
        }
    }
    return rules;
}

void CFGParser::errorRoutine() {
    std::cout << "Error in defining rules\n";
    exit(1);
}

void CFGParser::loadProperties(std::string propertiesFileName,
                               Properties::PropertiesData &propertiesData) {
    std::ifstream propertiesFile(propertiesFileName.c_str());
    handleFileNotFound(propertiesFile);
    propertiesFile >> propertiesData;
}

void CFGParser::handleFileNotFound(std::ifstream &file) {
    if (!file) {
        std::cout << "File not found" << std::endl;
        exit(0);
    }
}

void CFGParser::performLeftRecusiveElimination(std::map<Symbol, std::vector<Production>> *rules) {
    std::set<Symbol> nonTerminals;
    std::map<Symbol, std::vector<Production>>::iterator it;
    std::map<Symbol, std::vector<Production>> tempRules;
    for (it = rules->begin(); it != rules->end(); it++) {
        bool leftRecursive = false;
        Symbol nonTerminal = it->first;
        std::vector<Production> curRules = it->second;
        std::vector<Production> beta;
        std::vector<Production> alpha;
        /*iterating over productions for certain non terminal*/
        for (Production curRule : curRules) {
            Symbol firstSymbol = curRule.production.front();
            std::set<Symbol>::iterator ret;
            ret = nonTerminals.find(firstSymbol);
            /*check if the start of this production is defined before*/
            if (ret != nonTerminals.end()) {
                std::vector<Production> retRules = rules->find(*ret)->second;
                /*iterate over the productions of the predefined non terminal*/
                for (Production retRule : retRules) {
                    Symbol retFirstSymbol = retRule.production.front();
                    leftRecursive |= checkLeftRecusive(nonTerminal, retFirstSymbol, retRule, &alpha, &beta);
                }
            } else {
                leftRecursive |= checkLeftRecusive(nonTerminal, firstSymbol, curRule, &alpha, &beta);
            }
        }

        if (leftRecursive) {
            Symbol newNonTerminalSymbol;
            int i = 0;
            do {
                std::string newNonTerminalName = nonTerminal.name;
                newNonTerminalName.append(std::to_string(i));
                newNonTerminalSymbol.name = newNonTerminalName;
                i++;
            } while (rules->find(newNonTerminalSymbol) != rules->end());
             std::vector<Production> :: iterator betaIt;
            for (betaIt = beta.begin(); betaIt != beta.end(); betaIt++) {
                betaIt->production.push_back(newNonTerminalSymbol);
            }
            std::vector<Production> :: iterator alphaIt;
            for (alphaIt = alpha.begin(); alphaIt != alpha.end(); alphaIt++) {
                alphaIt->production.push_back(newNonTerminalSymbol);
            }
            Symbol eps("\\L", EPSILON);
            Production epsProduction;
            epsProduction.production.push_back(eps);
            alpha.push_back(epsProduction);
            it->second.clear();
            for (Production production : beta) {
                it->second.push_back(production);
            }
            tempRules.insert(std::pair<Symbol, std::vector<Production>>(newNonTerminalSymbol, alpha));
        }
        nonTerminals.insert(nonTerminal);
    }
    std::map<Symbol, std::vector<Production>>::iterator tempIt;
    for (tempIt = tempRules.begin(); tempIt != tempRules.end(); tempIt++) {
        rules->insert(std::pair<Symbol, std::vector<Production>> (tempIt->first, tempIt->second));
    }
}



bool CFGParser::checkLeftRecusive(Symbol &first, Symbol &rhsSymbol, Production &curRule,
                                  std::vector<Production> *alpha, std::vector<Production> *beta) {
    bool leftRecursive = false;
    /*check if it  is left recusive*/
    if (first == rhsSymbol) {
        leftRecursive = true;
        Production alphaI;
        for (int i = 1; i < curRule.production.size(); i++) {
            alphaI.production.push_back(curRule.production[i]);
        }
        alpha->push_back(alphaI);
    } else {
        beta->push_back(curRule);
    }
    return leftRecursive;
}

void CFGParser::performleftFactoring(std::map<Symbol, std::vector<Production>> *rules) {
    std::map<Symbol, std::vector<Production>>::iterator it;
    for (it = rules->begin(); it != rules->end(); it++) {
    }
}

static void checkLeftFactoring(std::map<Symbol, std::vector<Production>> *rules,
                               std::map<Symbol, std::vector<Production>>::iterator it) {
    bool leftfactoring = false;
    std::vector<Production> curRules = it->second;

}


bool CFGParser::checkRulesValidaty(std::map<Symbol, std::vector<Production>> *rules) {
    std::map<Symbol, std::vector<Production>>::iterator it;
    for (it = rules->begin(); it != rules->end(); it++) {
        std::vector<Production> curRules = it->second;
        for (Production curRule : curRules) {
            for (Symbol curSymbol : curRule.production) {
                if (curSymbol.type == NON_TERMINAL && rules->find(curSymbol) == rules->end()) {
                    return false;
                }
            }
        }
    }
    return true;
}