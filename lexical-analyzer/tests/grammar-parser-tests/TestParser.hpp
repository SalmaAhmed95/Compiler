#ifndef TEST_PARSER_H
#define TEST_PARSER_H

#include "TestHelper.hpp"
#include "gtest/gtest.h"
#include <fstream>
#include <set>
#include <utility>

std::string getRangeOr(char startC, char endC);
void testProductions(std::vector<Token *> realTokens,
                     std::vector<Token *> fakeTokens);

void validateFiles(std::string f1, std::string f2);

class TestParser : public ProductionParser, public ::testing::Test {

protected:
  TestParser();

  virtual ~TestParser();

  virtual void SetUp();

  virtual void TearDown();
};

#endif
