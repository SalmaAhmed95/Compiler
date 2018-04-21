#include "CFGParser.h"

class ProductionNode {
public:
    ProductionNode(Symbol _symbol);

    int getDependencyCount();

    void addDependent(ProductionNode *dependent);

    std::vector<ProductionNode *> getDependents();

    Symbol getSymbol();

    void setEps();

    bool containsEps();

    void changeDependencies(int val);

private:
    ProductionNode();

    Symbol symbol;
    std::vector<ProductionNode *> dependents;
    int dependencyCount;
    bool hasEps;
};
