#include "ProductionNode.h"

ProductionNode::ProductionNode(Symbol _symbol)
        : dependencyCount(0), symbol(_symbol), hasEps(false) {}

int ProductionNode::getDependencyCount() { return dependencyCount; }

void ProductionNode::addDependent(ProductionNode *dependent) {
    dependents.push_back(dependent);
}

Symbol ProductionNode::getSymbol() { return symbol; }

std::vector<ProductionNode *> ProductionNode::getDependents() {
    return dependents;
}

void ProductionNode::setEps() { hasEps = true; }

bool ProductionNode::containsEps() { return hasEps; }

void ProductionNode::changeDependencies(int val) { dependencyCount += val; }
