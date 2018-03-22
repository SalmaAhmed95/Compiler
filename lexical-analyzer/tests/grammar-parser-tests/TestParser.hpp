#ifndef TEST_PARSER_H
#define TEST_PARSER_H

#include "TestHelper.hpp"
#include "gtest/gtest.h"
#include <fstream>

std::string getRangeOr(char startC, char endC);

class TestParser : public ProductionParser, public ::testing::Test {

protected:
  TestParser();

  virtual ~TestParser();

  virtual void SetUp();

  virtual void TearDown();
};

#endif
