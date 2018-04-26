//
// Created by karfass on 18/04/2018.

#include "CFGParser.h"
#include <fstream>
#include <set>
#include <climits>
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

    performLeftRecursiveElimination(&rules);
    excuteLeftFactoring(&rules);
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
                if (curToken.length() != 0) {
                    errorRoutine();
                }
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

void CFGParser::performLeftRecursiveElimination(std::map<Symbol, std::vector<Production>> *rules) {
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
                    leftRecursive |= checkLeftRecursive(nonTerminal, retFirstSymbol, retRule, &alpha, &beta);
                    for (std::vector<Production> :: iterator itAlpha = alpha.begin(); itAlpha != alpha.end(); itAlpha++){
                        for (int i = 1; i < curRule.production.size(); i++) {
                            itAlpha->production.push_back(curRule.production[i]);
                        }
                    }
                    for (std::vector<Production> :: iterator itBeta = beta.begin(); itBeta != beta.end(); itBeta++){
                        for (int i = 1; i < curRule.production.size(); i++) {
                            itBeta->production.push_back(curRule.production[i]);
                        }
                    }
                }
            } else {
                leftRecursive |= checkLeftRecursive(nonTerminal, firstSymbol, curRule, &alpha, &beta);
            }
        }

        if (leftRecursive) {
            Symbol newNonTerminalSymbol (getNewSymbolName(&tempRules, rules, nonTerminal.name), NON_TERMINAL);
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



bool CFGParser::checkLeftRecursive(Symbol &first, Symbol &rhsSymbol, Production &curRule,
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

std::map<Symbol,std::vector<Production>> :: iterator CFGParser::performLeftFactoring(std::map<Symbol, std::vector<Production>> *tempRules,
                                                                                       std::map<Symbol,std::vector<Production>> *curRules,
                                                                                       std::vector<Production> &productions,
                                                                                       Symbol firstSymbol) {
    std::cout<<"perform left factoring\n";
    std::cout<<firstSymbol.name<<"55%\n";
       int index =  1;
       bool error = false;
       Production newProduction;
       while (index < productions[0].production.size()) {
           Symbol startSymbol = productions[0].production[index];
           std::cout<<startSymbol.name<<"\n";
           for (int i = 1; i < productions.size(); i++) {
               if (index >= productions[i].production.size() || productions[i].production[index] != startSymbol) {
                   error = true;
                   break;
               }
           }
           if (error){
               index--;
               break;
           }
           index++;
       }
       if (index == 1 && index >= productions[0].production.size() || index == productions[0].production.size()){
           index--;
       }
       std::cout<<index<< "updating\n";
       /*updates the production for the left factored rule*/
        for (int i = 0; i <= index; i++) {
            std::cout<<"start\n";
            std::cout<<productions[0].production[i].name<<"\n";
            newProduction.production.push_back(productions[0].production[i]);
        }

       /*create new rule*/
      std::vector<Production> newProductions;
      std::cout<<"new productions\n";
      bool remainingSymbols = false;
      int minimumSizeProduction = INT_MAX;
      for (int i = 0; i < productions.size(); i++) {
          Production newProduction;
          minimumSizeProduction = productions[i].production.size() < minimumSizeProduction ? productions[i].production.size() : minimumSizeProduction;
          for (int j = index + 1; j < productions[i].production.size(); j++) {
              newProduction.production.push_back(productions[i].production[j]);
          }
          if (!newProduction.production.empty()) {
              newProduction.print();
              remainingSymbols = true;
              newProductions.push_back(newProduction);
          }
      }

    Symbol newNonTerminalSymbol (getNewSymbolName(tempRules, curRules, firstSymbol.name), NON_TERMINAL);
    std::cout<<"new non Terminal"<<newNonTerminalSymbol.name<<"\n";
    if (remainingSymbols) {
        newProduction.production.push_back(newNonTerminalSymbol);
        if (index + 1 == minimumSizeProduction) {
            Symbol eps ("\\L",EPSILON);
            Production epsProduction;
            epsProduction.production.push_back(eps);
            newProductions.push_back(epsProduction);
        }

    }
    if (tempRules->find(firstSymbol) != tempRules->end()) {
        tempRules->find(firstSymbol)->second.push_back(newProduction);
    } else {
        std::vector<Production> newRule;
        newRule.push_back(newProduction);
        tempRules->insert(std::pair<Symbol, std::vector<Production>>(firstSymbol,newRule));
    }
    std::cout<<"new productions vector size#"<<newProductions.size()<<"\n";
   if (!newProductions.empty()) {
       return tempRules->insert(std::pair<Symbol, std::vector<Production>>(newNonTerminalSymbol, newProductions)).first;
   } else {
       return tempRules->end();
   }

}

void CFGParser::checkLeftFactoring(std::map<Symbol, std::vector<Production>> *tempRules,
                                     std::map<Symbol, std::vector<Production>> *curRules,
                                     std::map<Symbol, std::vector<Production>>::iterator it) {

    std::vector<Production> productions = it->second;
    std::cout<<"in check left facroring recusive \n";
    std::cout<<"nonTerminal name #"<<it->first.name<<"#\n";
    std::map<Symbol, std::vector<Production>> commonStart;
    for (int i = 0; i < productions.size(); i++) {
        Symbol startSymbol = productions.at(i).production.front();
        std::cout<<"symbol at first production "<<startSymbol.name<<"\n";
        std::map<Symbol, std::vector<Production>> :: iterator ret;
        ret = commonStart.find(startSymbol);
        if (ret != commonStart.end()) {
            ret->second.push_back(productions[i]);
        } else {
            std::vector<Production> indices;
            indices.push_back(productions[i]);
            commonStart.insert(std::pair<Symbol, std::vector<Production>> (startSymbol, std::vector <Production> (indices)));
        }
    }
    /*there's left recusive*/
    if (commonStart.size() != productions.size()) {
            std::cout<<"common start size"<<commonStart.size()<<"\n";
            it->second.clear();
            for (std::map<Symbol, std::vector<Production>> ::iterator itTemp = commonStart.begin(); itTemp != commonStart.end(); itTemp++){
                std::cout<<"for loop each has same beginning#"<<it->first.name<<"%\n";
                std::map<Symbol,std::vector<Production>> :: iterator returnLeft = performLeftFactoring(tempRules,curRules,itTemp->second, it->first);

                if (returnLeft != tempRules->end() && returnLeft->second.size() > 1) {
                    std::cout<<"return left#"<<returnLeft->first.name<<" "<<returnLeft->second.size()<<"\n";
                    checkLeftFactoring(tempRules, curRules, returnLeft);
                }
            }
    }
}

void CFGParser::excuteLeftFactoring(std::map<Symbol,std::vector<Production>> *curRules){
    std::map<Symbol,std::vector<Production>> tempRules;
    std::cout<<"in excute left factoring\n";
        for (std::map<Symbol, std::vector<Production>>::iterator it = curRules->begin(); it != curRules->end(); it++) {
            checkLeftFactoring(&tempRules, curRules, it);
        }

        for (std::map<Symbol, std::vector<Production>>::iterator itTemp = tempRules.begin();
             itTemp != tempRules.end(); itTemp++) {
            std::cout<<"temp to main#"<<itTemp->first.name<<"\n";
            std::map<Symbol,std::vector<Production>> :: iterator ret =curRules->find(itTemp->first);
            if (ret != curRules->end()) {
                std::cout<<"here\n";
                ret->second.clear();
                ret->second  = itTemp->second;
            } else{
                std::cout<<"here2    "<<itTemp->second.size()<<"\n";
                if(!itTemp->second.empty()) {
                    curRules->insert(std::pair<Symbol, std::vector<Production>>(itTemp->first, itTemp->second));
                }
            }
        }
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


std:: string CFGParser::getNewSymbolName (std::map<Symbol,std::vector<Production>> *tempRules, std::map<Symbol,std::vector<Production>> *curRules, std::string &firstSymbolName){
    int i = 0;
    Symbol newNonTerminalSymbol;
    std::string newNonTerminalName;
    std::cout<<"get new symbol name#"<<firstSymbolName<<"\n";
    std::cout<<"size of tempRules getSymbolName"<<tempRules->size()<<"\n";
    do {
        newNonTerminalName = firstSymbolName;
        newNonTerminalName.append(std::to_string(i));
        newNonTerminalSymbol.name = newNonTerminalName;
        i++;
    } while (curRules->find(newNonTerminalSymbol) != curRules->end() || tempRules->find(newNonTerminalSymbol) != tempRules->end());
    return newNonTerminalName;
}