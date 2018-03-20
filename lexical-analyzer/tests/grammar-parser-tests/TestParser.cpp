#include "TestParser.hpp"

const std::string propertiesFileName = "test-files/properties.ini";

TestParser::TestParser() {}

TestParser::~TestParser(){};

void TestParser::SetUp() {
  std::ofstream file(propertiesFileName.c_str());
  file << REG_DEF_EQU << " = =\n";
  file << REG_EXP_EQU << " = :\n";
  file << START_RESERVED_ENCLOSING << " = {\n";
  file << END_PUNC_ENCLOSING << " = }\n";
  file << END_PUNC_ENCLOSING << " = ]\n";
  file << START_PUNC_ENLCOSING << " = [\n";
  file << LAMBDA << " = \\L";
};

void TestParser::TearDown(){};

// TEST_F(TestParser, TestingTrimSpacesAtEnd) {
//   std::string trimmed = trim("  untrimmed text  ", " ");
//   EXPECT_EQ("untrimmed text", trimmed);
// }
//
// TEST_F(TestParser, TestingTrimTabsAtEnd) {
//   std::string trimmed = trim("\t\tuntrimmed text\t\t\t\t\t\t", "\t");
//   EXPECT_EQ("untrimmed text", trimmed);
// }
//
// TEST_F(TestParser, TestingTrimSpacesTabsMix) {
//   std::string trimmed = trim("\t\t    untrimmed text\t\t\t \t \t \t", " \t");
//   EXPECT_EQ("untrimmed text", trimmed);
// }
//
// TEST_F(TestParser, TestFormulateSpacesWithSpaces) {
//   std::string formulated =
//       formulateSpaces("\t\tuntrimmed        \ttext\t\t\t \t \t \t", " ", "
//       \t");
//   EXPECT_EQ("untrimmed text", formulated);
// }
// //
// // TEST_F(TestParser, TrivialProductionParserTest) {
// //   std::vector<Token *> tokens = ProductionParser::loadLexicalRules(
// //       "test-files/TrivialProductionParserTest.txt", propertiesFileName);
// //   EXPECT_EQ((int)tokens.size(), 1);
// //   std::string lower = getRangeOr('a', 'z'), upper = getRangeOr('A', 'Z');
// //   std::string digits = getRangeOr('0', '9');
// //   for (char i = startC; i <= endC; i++) {
// //     str = str + i + "|";
// //   }
// // }
