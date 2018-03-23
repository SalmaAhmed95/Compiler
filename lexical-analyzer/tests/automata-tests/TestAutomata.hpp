#ifndef TEST_AUTOMATA_H
#define TEST_AUTOMATA_H

#include "../../automata/Automata.h"
#include "../../automata/DFA.h"
#include "../../automata/NFA.h"
#include "gtest/gtest.h"

void testNodeCreation(Automata *automata, stateID realNodeId, stateID nodeId,
                      bool acceptance, bool phi, int rootId,
                      StateType stateType, std::string tokenClass,
                      int precedence, int numberOfStates);

void testTrans(std::set<char> trans, char startTrans, char endTrans);

void testGetTransOfNode(std::vector<TransEdges> transition, char startChar,
                        char endChar);

class TestAutomata : public ::testing::Test {

protected:
  TestAutomata();

  virtual ~TestAutomata();

  virtual void SetUp();

  virtual void TearDown();
};

#endif
