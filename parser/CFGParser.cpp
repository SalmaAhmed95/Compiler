//
// Created by karfass on 18/04/2018.

#include "CFGParser.h"


#include <fstream>
#include "../lexical-analyzer/utils/StringUtils.h"

#define START_LINE '#'
#define TERMINAL_IDENTIFIER '\''
#define OR_SEPARATOR  '|'

const std::string  DEFINITION_SEPARATOR =  "::==";
const std::string LAMBDA_SYMBOL = "\\l";


void CFGParser::parseLine(std::string &curRule, std::map <Symbol, std::vector<Production>> *rules){
    size_t index = StringUtils::getFirstChar(curRule);
    if (index != std::string::npos && curRule.at(index) == START_LINE) {
        curRule = curRule.erase(0,index + 1);
        std::vector<std::string> tokens = StringUtils::splitString(curRule, DEFINITION_SEPARATOR);
        if (tokens.size() != 2) {
            errorRoutine();
        } else {
            std::string nonTerminal = StringUtils::trimWhiteSpaces(tokens[0]);
            Symbol newSymbol(nonTerminal, NON_TERMINAL);
            if (rules->empty()) {
                newSymbol.type = START;
            }
            std::vector<Production> productions = calculateProductions(tokens[1]);

            std::map<Symbol,std::vector<Production>> :: iterator it;
            it = rules->find(newSymbol);

            if (it != rules->end()) {
                std::vector<Production> curRules = it->second;
                for (Production production : productions){
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
std::map<Symbol, std::vector<Production>> CFGParser :: getCFGRules(std::string rulesFileName, std::string propertiesFileName){
    std::map<Symbol, std::vector<Production>> rules;
    std::ifstream inFile = openFile(rulesFileName);
    Properties::PropertiesData propertiesData;
    loadProperties(propertiesFileName, propertiesData);
    std::string curRule;
    std::string curLine;
    while (std::getline(inFile,curLine)) {
       size_t index = StringUtils::getFirstChar(curLine);
       if (index != std::string::npos && curLine.at(index) == START_LINE) {
            if (!curRule.empty()) {
                parseLine(curRule, &rules);
            }
      }
      curRule.append(curLine);
    }
    if (!curRule.empty()) {
        parseLine(curRule, &rules);
    }
    inFile.close();
    return rules;
};

std::ifstream CFGParser::openFile (std::string fileName){
    std::ifstream inFile;
    inFile.open(fileName);
    if (!inFile) {
        std::cout<<"Unable to find grammer rules file";
        exit(1);
    }
    return inFile;
};


std::vector<Production> CFGParser::calculateProductions(std::string &rhs){
        std::vector<Production> rules;
        std::string curToken;
        bool singleQuoteFound = false;
        bool error = false;
        Production newProduction;
        rules.push_back(newProduction);
        for (std::size_t index = 0; index < rhs.length(); index++) {
            char curChar = rhs.at(index);
            if (StringUtils::isDelimiter(curChar)){
                 if (!singleQuoteFound) {
                     if (curToken.length() != 0){
                         Symbol newNonTerminal (curToken, NON_TERMINAL);
                         rules.back().production.push_back(newNonTerminal);
                         curToken.clear();
                     }
                 }
            } else if (curChar == TERMINAL_IDENTIFIER){
                if (!singleQuoteFound) {
                    singleQuoteFound = true;
                } else {
                    if (curToken.length() != 0){
                        Symbol newTerminal (curToken, TERMINAL);
                        rules.back().production.push_back(newTerminal);
                        singleQuoteFound = false;
                        curToken.clear();
                    }
                }
            } else if (curChar == OR_SEPARATOR && index > 0 && rhs.at(index - 1) != '\\') {
                if (singleQuoteFound) {
                        errorRoutine();
                    } else {
                        if (curToken.length() != 0){
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
                curToken.append(1,curChar);
                Symbol newTerminal (curToken, EPSILION);
                rules.back().production.push_back(newTerminal);
                curToken.clear();
            } else {
                curToken.append(1,curChar);
            }
        }

        if (singleQuoteFound) {
            errorRoutine();
        } else {
            if (!curToken.empty()){
                Symbol newTerminal(curToken, NON_TERMINAL);
                rules.back().production.push_back(newTerminal);
            }
        }
    return rules;
}

 void CFGParser::errorRoutine(){
    std::cout<<"Error in defining rules\n";
    exit(1);
}

void CFGParser::loadProperties(std::string propertiesFileName,
                           Properties::PropertiesData &propertiesData){
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