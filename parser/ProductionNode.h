#include "CFGParser.h"

class ProductionNode {
public:
    ProductionNode(Symbol _symbol);

    int getDependenceyCount();

    void addDependent(ProductionNode *dependent);

    std::vector<ProductionNode *> getDependents();

    Symbol getSymbol();

    void setEps();

    bool containsEps();

    void changeDependecies(int val);

private:
    ProductionNode();

    Symbol symbol;
    std::vector<ProductionNode *> dependents;
    int dependenceyCount;
    bool hasEps;
};
