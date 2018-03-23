#ifndef TEST_NFA_TO_DFA_CONVERTER_H
#define TEST_NFA_TO_DFA_CONVERTER_H

#include "../../automata/Automata.h"
#include "../../automata/NFA.h"
#include "../../automata/RegexToNfaConverter.hpp"
#include "../grammar-parser-tests/TestHelper.hpp"
#include "gtest/gtest.h"

class TestNfaToDfaConverter : public ::testing::Test {

protected:
  TestNfaToDfaConverter();

  virtual ~TestNfaToDfaConverter();

  virtual void SetUp();

  virtual void TearDown();
};

#endif
