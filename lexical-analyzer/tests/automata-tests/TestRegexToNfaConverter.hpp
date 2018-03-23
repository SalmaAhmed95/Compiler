#ifndef TEST_REGEX_TO_NFA_CONVERTER_H
#define TEST_REGEX_TO_NFA_CONVERTER_H

#include "../../automata/Automata.h"
#include "../../automata/NFA.h"
#include "../../automata/RegexToNfaConverter.hpp"
#include "../grammar-parser-tests/TestHelper.hpp"
#include "gtest/gtest.h"

class TestRegexToNfaConverter : public ::testing::Test {

protected:
  TestRegexToNfaConverter();

  virtual ~TestRegexToNfaConverter();

  virtual void SetUp();

  virtual void TearDown();
};

#endif
