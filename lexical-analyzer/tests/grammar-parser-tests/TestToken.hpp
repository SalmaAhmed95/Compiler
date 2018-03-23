#include "../../grammar-parser/Token.hpp"
#include "gtest/gtest.h"

class TestToken : public ::testing::Test {

protected:
  TestToken();

  virtual ~TestToken();

  virtual void SetUp();

  virtual void TearDown();
};
