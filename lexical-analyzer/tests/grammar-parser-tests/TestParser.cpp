// #include "TestParser.hpp"
//
// const std::string propertiesFileName = "test-files/properties.ini";
//
// TestParser::TestParser() {}
//
// TestParser::~TestParser(){};
//
// void TestParser::SetUp() {
//   std::ofstream file(propertiesFileName.c_str());
//   file << REG_DEF_EQU << " = =\n";
//   file << REG_EXP_EQU << " = :\n";
//   file << START_RESERVED_ENCLOSING << " = {\n";
//   file << END_PUNC_ENCLOSING << " = }\n";
//   file << END_PUNC_ENCLOSING << " = ]\n";
//   file << START_PUNC_ENLCOSING << " = [\n";
//   file << LAMBDA << " = \\L";
// };
//
// void TestParser::TearDown(){};
//
// TEST_F(TestParser, TrivialDigitOneTokenTest1) {
//   std::vector<std::string> fakeTokensType, fakeTokensRegex;
//   std::vector<int> fakeTokensPrecedence;
//   fakeTokensType.push_back("digit");
//   fakeTokensRegex.push_back("01|2|3|4|5|6|7|8|9|");
//   fakeTokensPrecedence.push_back(10);
// }
