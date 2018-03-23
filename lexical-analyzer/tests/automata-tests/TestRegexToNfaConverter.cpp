#include "TestRegexToNfaConverter.hpp"

const std::string TRANSITIONS_MISS_MATCH = "Transitions miss match";

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
      new NFA((int)std::min('a', EPS_TRANS), (int)std::max('a', EPS_TRANS));
  for (int i = 0; i < 5; i++) {
    fakeNfa->createNode();
  }
  fakeNfa->addTransition(EPS_TRANS, 0, 1);
  fakeNfa->addTransition(EPS_TRANS, 1, 2);
  fakeNfa->addTransition('a', 2, 3);
  fakeNfa->addTransition(EPS_TRANS, 3, 4);
  fakeNfa->addTransition(EPS_TRANS, 3, 2);
  fakeNfa->addTransition(EPS_TRANS, 1, 4);
  ASSERT_TRUE(fakeNfa->getNumberOfStates() == nfa->getNumberOfStates());
}
