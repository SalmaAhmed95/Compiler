// #include "TestToken.hpp"
//
// TestToken::TestToken() {}
//
// TestToken::~TestToken(){};
//
// void TestToken::SetUp(){};
//
// void TestToken::TearDown(){};
//
// TEST(TestToken, TrivialMultiParameterConstructorToken) {
//   struct RegexChar *r1 = new RegexChar, *r2 = new RegexChar,
//                    *r3 = new RegexChar, *r4 = new RegexChar,
//                    *r5 = new RegexChar;
//   r1->c = 'x', r1->charType = CHAR, r2->c = '|', r1->charType = OPERATOR;
//   r3->c = 't', r3->charType = CHAR, r4->c = '-', r4->charType = OPERATOR;
//   r5->c = 'z', r5->charType = CHAR;
//   std::vector<RegexChar *> expectedV;
//   expectedV.push_back(r1), expectedV.push_back(r2), expectedV.push_back(r3),
//       expectedV.push_back(r4), expectedV.push_back(r5);
//   Token token("Identifier", expectedV, 10);
//   EXPECT_EQ(token.getType(), "Identifier");
//   EXPECT_EQ(token.getPriority(), 10);
//   EXPECT_EQ(token.getPostfixRegix().size(), expectedV.size());
//   for (int i = 0; i < expectedV.size(); i++) {
//     EXPECT_EQ(token.getPostfixRegix()[i]->c, expectedV[i]->c);
//     EXPECT_EQ(token.getPostfixRegix()[i]->charType, expectedV[i]->charType);
//   }
// }
