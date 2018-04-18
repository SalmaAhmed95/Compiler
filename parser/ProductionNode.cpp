#include "ProductionNode.h"

ProductionNode::ProductionNode(Symbol _symbol)
    : dependenceyCount(0), symbol(_symbol), hasEps(false) {}

int ProductionNode::getDependenceyCount() { return dependenceyCount; }

void ProductionNode::addDependent(ProductionNode *dependent) {
  dependents.push_back(dependent);
}

std::vector<ProductionNode *> ProductionNode::getDependents() {
  return dependents;
}

void ProductionNode::setEps() { hasEps = true; }

bool ProductionNode::containsEps() { return hasEps; }

void ProductionNode::changeDependecies(int val) { dependenceyCount += val; }
