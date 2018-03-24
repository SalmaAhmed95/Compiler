#include "TestRegexToNfaConverter.hpp"

const std::string TRANSITIONS_MISS_MATCH = "Transitions miss match";
const std::string NFA_MISS_MATCH = "NFA miss match";

TestRegexToNfaConverter::TestRegexToNfaConverter() {}

TestRegexToNfaConverter::~TestRegexToNfaConverter(){};

void TestRegexToNfaConverter::SetUp(){

};

void TestRegexToNfaConverter::TearDown(){};

TEST(TestRegexToNfaConverter, StarTest_1) {
  std::vector<std::string> fakeTokensType, fakeTokensRegex;
  std::vector<int> fakeTokensPrecedence;
  addTokenToList("star", "a*", 10, fakeTokensType, fakeTokensRegex,
                 fakeTokensPrecedence);
  std::vector<Token *> fakeTokens =
      buildTokens(fakeTokensType, fakeTokensRegex, fakeTokensPrecedence);
  NFA *nfa = RegexToNfaConverter::getNfa(fakeTokens);
  NFA *fakeNfa =
      new NFA((int)std::min(EPS_TRANS, 'a'), (int)std::max('a', STAR_OP));
  for (int i = 0; i < 5; i++) {
    fakeNfa->createNode();
  }
  fakeNfa->addTransition(EPS_TRANS, 0, 3);
  fakeNfa->addTransition(EPS_TRANS, 1, 2);
  fakeNfa->addTransition('a', 1, 2);
  fakeNfa->addTransition(EPS_TRANS, 3, 1);
  fakeNfa->addTransition(EPS_TRANS, 3, 4);
  fakeNfa->addTransition(EPS_TRANS, 2, 1);
  ASSERT_TRUE(fakeNfa->getNumberOfStates() == nfa->getNumberOfStates())
      << NFA_MISS_MATCH;
  nfaTraversalTest(fakeNfa, nfa, 0, 0);
  EXPECT_TRUE(nfa->isAccepted(4));
  EXPECT_EQ(nfa->getTokenClass(4), "star");
  deleteNfas(fakeNfa, nfa);
  deleteTokens(fakeTokens);
}

TEST(TestRegexToNfaConverter, OrTest_2) {
  std::vector<std::string> fakeTokensType, fakeTokensRegex;
  std::vector<int> fakeTokensPrecedence;
  addTokenToList("Or", "ab|", 10, fakeTokensType, fakeTokensRegex,
                 fakeTokensPrecedence);
  std::vector<Token *> fakeTokens =
      buildTokens(fakeTokensType, fakeTokensRegex, fakeTokensPrecedence);
  NFA *nfa = RegexToNfaConverter::getNfa(fakeTokens);
  NFA *fakeNfa =
      new NFA((int)std::min(EPS_TRANS, OR_OP), (int)std::max(EPS_TRANS, OR_OP));
  for (int i = 0; i < 7; i++) {
    fakeNfa->createNode();
  }
  fakeNfa->addTransition('a', 1, 2);
  fakeNfa->addTransition('b', 3, 4);
  fakeNfa->addTransition(EPS_TRANS, 5, 1);
  fakeNfa->addTransition(EPS_TRANS, 5, 3);
  fakeNfa->addTransition(EPS_TRANS, 2, 6);
  fakeNfa->addTransition(EPS_TRANS, 4, 6);
  fakeNfa->addTransition(EPS_TRANS, 0, 5);
  ASSERT_TRUE(fakeNfa->getNumberOfStates() == nfa->getNumberOfStates())
      << NFA_MISS_MATCH;
  nfaTraversalTest(fakeNfa, nfa, 0, 0);
  EXPECT_TRUE(nfa->isAccepted(6));
  EXPECT_EQ(nfa->getTokenClass(6), "Or");
  deleteNfas(fakeNfa, nfa);
  deleteTokens(fakeTokens);
}

TEST(TestRegexToNfaConverter, ConcatenateTest_3) {
  std::vector<Token *> fakeTokens;
  std::vector<RegexChar *> reg;
  reg.push_back(ProductionParser::makeRegexChar('a', CHAR));
  reg.push_back(ProductionParser::makeRegexChar('b', CHAR));
  reg.push_back(ProductionParser::makeRegexChar('#', OPERATOR));
  fakeTokens.push_back(new Token("concatenate", reg, 10));
  NFA *nfa = RegexToNfaConverter::getNfa(fakeTokens);
  NFA *fakeNfa =
      new NFA((int)std::min(EPS_TRANS, 'b'), (int)std::max(CONC_OP, 'b'));
  for (int i = 0; i < 5; i++) {
    fakeNfa->createNode();
  }
  fakeNfa->addTransition('a', 1, 2);
  fakeNfa->addTransition('b', 3, 4);
  fakeNfa->addTransition(EPS_TRANS, 2, 3);
  fakeNfa->addTransition(EPS_TRANS, 0, 1);
  ASSERT_TRUE(fakeNfa->getNumberOfStates() == nfa->getNumberOfStates())
      << NFA_MISS_MATCH;
  nfaTraversalTest(fakeNfa, nfa, 0, 0);
  EXPECT_TRUE(nfa->isAccepted(4));
  EXPECT_EQ(nfa->getTokenClass(4), "concatenate");
  deleteNfas(fakeNfa, nfa);
  deleteTokens(fakeTokens);
}

TEST(TestRegexToNfaConverter, PlusTest_4) {
  std::vector<std::string> fakeTokensType, fakeTokensRegex;
  std::vector<int> fakeTokensPrecedence;
  addTokenToList("Plus", "a+", 10, fakeTokensType, fakeTokensRegex,
                 fakeTokensPrecedence);
  std::vector<Token *> fakeTokens =
      buildTokens(fakeTokensType, fakeTokensRegex, fakeTokensPrecedence);
  NFA *nfa = RegexToNfaConverter::getNfa(fakeTokens);
  NFA *fakeNfa =
      new NFA((int)std::min(EPS_TRANS, 'a'), (int)std::max(PLUS_OP, 'a'));
  for (int i = 0; i < 4; i++) {
    fakeNfa->createNode();
  }
  fakeNfa->addTransition('a', 1, 2);
  fakeNfa->addTransition(EPS_TRANS, 2, 1);
  fakeNfa->addTransition(EPS_TRANS, 2, 3);
  fakeNfa->addTransition(EPS_TRANS, 0, 1);
  ASSERT_TRUE(fakeNfa->getNumberOfStates() == nfa->getNumberOfStates())
      << NFA_MISS_MATCH;
  nfaTraversalTest(fakeNfa, nfa, 0, 0);
  EXPECT_TRUE(nfa->isAccepted(3));
  EXPECT_EQ(nfa->getTokenClass(3), "Plus");
  deleteNfas(fakeNfa, nfa);
  deleteTokens(fakeTokens);
}

TEST(TestRegexToNfaConverter, CombinedMultiTest_5) {
  std::vector<RegexChar *> reg;
  makeSpecialReg(reg);
  std::vector<RegexChar *> reg2;
  reg2.push_back(ProductionParser::makeRegexChar('a', CHAR));
  reg2.push_back(ProductionParser::makeRegexChar('b', CHAR));
  reg2.push_back(ProductionParser::makeRegexChar(OR_OP, OPERATOR));
  std::vector<Token *> fakeTokens;
  fakeTokens.push_back(new Token("combined", reg, 10));
  fakeTokens.push_back(new Token("combined2", reg2, 20));
  NFA *nfa = RegexToNfaConverter::getNfa(fakeTokens);
  NFA *fakeNfa =
      new NFA((int)std::min(EPS_TRANS, CONC_OP), (int)std::max(OR_OP, CONC_OP));
  for (int i = 0; i < 22; i++) {
    fakeNfa->createNode();
  }
  fakeNfa->addTransition(EPS_TRANS, 1, 20);
  fakeNfa->addTransition(EPS_TRANS, 20, 16);
  fakeNfa->addTransition(EPS_TRANS, 20, 18);
  fakeNfa->addTransition(EPS_TRANS, 17, 21);
  fakeNfa->addTransition(EPS_TRANS, 19, 21);
  fakeNfa->addTransition('a', 16, 17);
  fakeNfa->addTransition('b', 18, 19);
  addSpecialTrans(fakeNfa);
  ASSERT_TRUE(fakeNfa->getNumberOfStates() == nfa->getNumberOfStates())
      << NFA_MISS_MATCH;
  nfaTraversalTest(fakeNfa, nfa, 0, 0);
  EXPECT_TRUE(nfa->isAccepted(15));
  EXPECT_EQ(nfa->getTokenClass(15), "combined");
  EXPECT_TRUE(nfa->isAccepted(21));
  EXPECT_EQ(nfa->getTokenClass(21), "combined2");
  deleteNfas(fakeNfa, nfa);
  deleteTokens(fakeTokens);
}

TEST(TestRegexToNfaConverter, CombinedSingleTest_5) {
  std::vector<RegexChar *> reg;
  makeSpecialReg(reg);
  std::vector<Token *> fakeTokens;
  fakeTokens.push_back(new Token("combined", reg, 10));
  NFA *nfa = RegexToNfaConverter::getNfa(fakeTokens);
  NFA *fakeNfa =
      new NFA((int)std::min(EPS_TRANS, CONC_OP), (int)std::max(OR_OP, CONC_OP));
  for (int i = 0; i < 16; i++) {
    fakeNfa->createNode();
  }
  addSpecialTrans(fakeNfa);
  ASSERT_TRUE(fakeNfa->getNumberOfStates() == nfa->getNumberOfStates())
      << NFA_MISS_MATCH;
  nfaTraversalTest(fakeNfa, nfa, 0, 0);
  EXPECT_TRUE(nfa->isAccepted(15));
  EXPECT_EQ(nfa->getTokenClass(15), "combined");
  deleteNfas(fakeNfa, nfa);
  deleteTokens(fakeTokens);
}

void makeSpecialReg(std::vector<RegexChar *> &reg) {
  reg.push_back(ProductionParser::makeRegexChar('a', CHAR));
  reg.push_back(ProductionParser::makeRegexChar(PLUS_OP, OPERATOR));
  reg.push_back(ProductionParser::makeRegexChar('a', CHAR));
  reg.push_back(ProductionParser::makeRegexChar('b', CHAR));
  reg.push_back(ProductionParser::makeRegexChar(CONC_OP, OPERATOR));
  reg.push_back(ProductionParser::makeRegexChar('c', CHAR));
  reg.push_back(ProductionParser::makeRegexChar(OR_OP, OPERATOR));
  reg.push_back(ProductionParser::makeRegexChar(OR_OP, OPERATOR));
  reg.push_back(ProductionParser::makeRegexChar(STAR_OP, OPERATOR));
}

void addSpecialTrans(NFA *fakeNfa) {
  fakeNfa->addTransition(EPS_TRANS, 0, 14);
  fakeNfa->addTransition(EPS_TRANS, 14, 15);
  fakeNfa->addTransition(EPS_TRANS, 14, 12);
  fakeNfa->addTransition(EPS_TRANS, 12, 10);
  fakeNfa->addTransition(EPS_TRANS, 12, 1);
  fakeNfa->addTransition('a', 1, 2);
  fakeNfa->addTransition(EPS_TRANS, 2, 1);
  fakeNfa->addTransition(EPS_TRANS, 2, 3);
  fakeNfa->addTransition(EPS_TRANS, 3, 13);
  fakeNfa->addTransition(EPS_TRANS, 10, 4);
  fakeNfa->addTransition(EPS_TRANS, 10, 8);
  fakeNfa->addTransition('c', 8, 9);
  fakeNfa->addTransition(EPS_TRANS, 9, 11);
  fakeNfa->addTransition('a', 4, 5);
  fakeNfa->addTransition(EPS_TRANS, 5, 6);
  fakeNfa->addTransition('b', 6, 7);
  fakeNfa->addTransition(EPS_TRANS, 7, 11);
  fakeNfa->addTransition(EPS_TRANS, 11, 13);
  fakeNfa->addTransition(EPS_TRANS, 13, 15);
}

void nfaTraversalTest(NFA *fakeNfa, NFA *realNfa, stateID fakeNfaNodeId,
                      stateID realNfaNodeId) {
  std::vector<TransEdges> fakeTranses = fakeNfa->getTransitions(fakeNfaNodeId);
  std::vector<TransEdges> realTranses = realNfa->getTransitions(realNfaNodeId);
  std::sort(fakeTranses.begin(), fakeTranses.end(), edgesCmp);
  std::sort(realTranses.begin(), realTranses.end(), edgesCmp);
  ASSERT_TRUE(fakeTranses.size() == realTranses.size()) << NFA_MISS_MATCH;
  for (int i = 0; i < (int)fakeTranses.size(); i++) {
    ASSERT_TRUE(fakeTranses[i].transition == realTranses[i].transition)
        << NFA_MISS_MATCH;
    std::vector<stateID> fakeNextStates = fakeTranses[i].nextStates;
    std::vector<stateID> realNextStates = realTranses[i].nextStates;
    std::sort(fakeNextStates.begin(), fakeNextStates.end());
    std::sort(realNextStates.begin(), realNextStates.end());
    ASSERT_TRUE(realNextStates.size() == fakeNextStates.size())
        << NFA_MISS_MATCH;
    for (int j = 0; j < (int)fakeNextStates.size(); j++) {
      stateID nextFakeId = fakeNextStates[j];
      stateID nextRealId = realNextStates[i];
      ASSERT_TRUE(nextFakeId == nextRealId) << NFA_MISS_MATCH;
      nfaTraversalTest(fakeNfa, realNfa, nextFakeId, nextRealId);
    }
  }
}

bool edgesCmp(struct TransEdges e1, struct TransEdges e2) {
  if (e1.transition != e2.transition) {
    return e1.transition < e2.transition;
  }
  return e1.nextStates.size() < e2.nextStates.size();
}

void deleteTokens(std::vector<Token *> &t) {
  for (int i = 0; i < (int)t.size(); i++) {
    if (t[i] != NULL) {
      delete t[i];
    }
  }
}

void deleteNfas(NFA *n1, NFA *n2) {
  if (n1 != NULL) {
    delete n1;
  }
  if (n2 != NULL) {
    delete n2;
  }
}
