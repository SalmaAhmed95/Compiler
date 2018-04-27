#ifndef COMPLIER_GRAMMAR_H
#define COMPLIER_GRAMMAR_H

#include "CFGParser.h"
#include "ProductionNode.h"
#include "ParsingTable.h"
#include <map>
#include <queue>
#include <set>
#include <vector>

#define END "`"

class Grammar {

public:

    ParsingTable* getGrammarTable(std::string fileName);

    bool isTerminal(Symbol t);

private:
    std::map<Symbol, std::set<Symbol>> first, follow;
    std::set<Symbol> terminals, nonTerminals;
    ParsingTable* parsingTable = new ParsingTable;


    void constructTerminals(std::map<Symbol, std::vector<Production>> rules);

    void constructNonTerminals(std::map<Symbol, std::vector<Production>> rules);

    void buildNodes(std::vector<ProductionNode *> &nodes,
                    std::map<Symbol, ProductionNode *> &graph,
                    std::map<Symbol, std::vector<Production>> rules);

    void buildGraph(std::map<Symbol, std::vector<Production>> rules,
                    std::vector<ProductionNode *> &nodes,
                    std::map<Symbol, ProductionNode *> &graph);

    void constructFirst(std::map<Symbol, std::vector<Production>> rules);

    bool hasEpsilon(std::set<Symbol> first);

    void constructFollowSet(std::map<Symbol, std::vector<Production>> rules);

    void constructParsingTable(std::map<Symbol, std::vector<Production>> rules);

    void addSyncEntries(std::map<Symbol, std::set<Symbol>> follow);

    void printSets(std::map<Symbol, std::set<Symbol>> set);
};
#endif
