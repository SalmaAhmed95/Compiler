#ifndef COMPLIER_GRAMMAR_H
#define COMPLIER_GRAMMAR_H

#include "CFGParser.h"
#include "ProductionNode.h"
#include <map>
#include <queue>
#include <set>
#include <vector>

#define END "`"

class Grammar {

public:

    ParsingTable getGrammerTable(std::string fileName);


private:
    std::map<Symbol, std::set<Symbol>> first, follow;
    std::set<Symbol> terminals, nonTerminals;
    ParsingTable parsingTable;


    void constructTerminals(std::map<Symbol, std::vector<Production>> rules);

    void constructNonTerminals(std::map<Symbol, std::vector<Production>> rules);

    void buildNodes(std::vector<ProductionNode *> &nodes,
                    std::map<Symbol, ProductionNode *> &graph,
                    std::map<Symbol, std::vector<Production>> rules);

    void buildGraph(std::map<Symbol, std::vector<Production>> rules,
                    std::vector<ProductionNode *> &nodes,
                    std::map<Symbol, ProductionNode *> &graph);

    void constructFirst(std::map<Symbol, std::vector<Production>> rules);

    bool isTerminal(Symbol t);

    bool hasEpsilon(std::set<Symbol> first);

    void constructFollowSet(std::map<Symbol, std::vector<Production>> rules);

    void constructParsingTable(std::map<Symbol, std::vector<Production>> rules);

    void printSets(std::map<Symbol, std::set<Symbol>> set);

    void printParsingTable(ParsingTable parsingTable);

};

#endif
