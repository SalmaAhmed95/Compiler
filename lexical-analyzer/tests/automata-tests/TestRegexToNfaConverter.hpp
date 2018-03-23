#ifndef TEST_REGEX_TO_NFA_CONVERTER_H
#define TEST_REGEX_TO_NFA_CONVERTER_H

#include "../../automata/Automata.h"
#include "../../automata/NFA.h"
#include "../../automata/RegexToNfaConverter.hpp"
#include "../grammar-parser-tests/TestHelper.hpp"
#include "gtest/gtest.h"

void nfaTraversalTest(NFA *fakeNfa, NFA *realNfa, stateID fakeNfaNodeId,
                      stateID realNfaNodeId);
bool edgesCmp(struct TransEdges e1, struct TransEdges e2);

void makeSpecialReg(std::vector<RegexChar *> &reg);
void addSpecialTrans(NFA *fakeNfa);
void deleteTokens(std::vector<Token *> &t);
void deleteNfas(NFA *n1, NFA *n2);

class TestRegexToNfaConverter : public ::testing::Test {

protected:
  TestRegexToNfaConverter();

  virtual ~TestRegexToNfaConverter();

  virtual void SetUp();

  virtual void TearDown();
};

#endif
