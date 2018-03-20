#include "TestToken.hpp"

TestToken::TestToken() {}

TestToken::~TestToken(){};

void TestToken::SetUp(){};

void TestToken::TearDown(){};

// TEST(TestToken, TrivialMultiParameterConstructorToken) {
//   Token token("Identifier", "x|y-z", 10);
//   EXPECT_EQ(token.getType(), "Identifier");
//   EXPECT_EQ(token.getPostfixRegix(), "x|y-z");
//   EXPECT_EQ(token.getPriority(), 10);
// }
//
// TEST(TestToken, TrivialSetterGetterType) {
//   Token token;
//   token.setType("Identifier");
//   EXPECT_EQ(token.getType(), "Identifier");
// }
//
// TEST(TestToken, TrivialSetterGetterRegex) {
//   Token token;
//   token.setPostfixRegex("x|y-z");
//   EXPECT_EQ(token.getPostfixRegix(), "x|y-z");
// }
//
// TEST(TestToken, TrivialSetterGetterPriority) {
//   Token token;
//   token.setPriority(10);
//   EXPECT_EQ(token.getPriority(), 10);
// }
