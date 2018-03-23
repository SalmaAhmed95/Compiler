#include "TestParser.hpp"

const std::string propertiesFileName = "test-files/properties.ini";
const std::string FILE_NOT_FOUND = "File not found exception";

TestParser::TestParser() {}

TestParser::~TestParser(){};

void TestParser::SetUp() {
  std::ofstream file(propertiesFileName.c_str());
  ASSERT_TRUE(file != NULL);
  file << REG_DEF_EQU << " = =\n";
  file << REG_EXP_EQU << " = :\n";
  file << START_RESERVED_ENCLOSING << " = {\n";
  file << END_RESERVED_ENCLOSING << " = }\n";
  file << END_PUNC_ENCLOSING << " = ]\n";
  file << START_PUNC_ENLCOSING << " = [\n";
  file << LAMBDA << " = \\L";
};

void TestParser::TearDown(){};

TEST_F(TestParser, TrivialDigitOneTokenTest_1) {
  std::vector<std::string> fakeTokensType, fakeTokensRegex;
  std::vector<int> fakeTokensPrecedence;
  addTokenToList("digit", "01|2|3|4|5|6|7|8|9|", DEFAULT_PRIORITY,
                 fakeTokensType, fakeTokensRegex, fakeTokensPrecedence);
  std::vector<Token *> fakeTokens =
      buildTokens(fakeTokensType, fakeTokensRegex, fakeTokensPrecedence);
  validateFiles("test-files/TrivialDigitOneTokenTest_1.txt",
                propertiesFileName);
  std::vector<Token *> realTokens = ProductionParser::loadLexicalRules(
      "test-files/TrivialDigitOneTokenTest_1.txt", propertiesFileName);
  testProductions(realTokens, fakeTokens);
}

TEST_F(TestParser, DigitOneTokenSpacesAndTabs_2) {
  std::vector<std::string> fakeTokensType, fakeTokensRegex;
  std::vector<int> fakeTokensPrecedence;
  addTokenToList("digit", "01|2|3|4|5|6|7|8|9|", DEFAULT_PRIORITY,
                 fakeTokensType, fakeTokensRegex, fakeTokensPrecedence);
  std::vector<Token *> fakeTokens =
      buildTokens(fakeTokensType, fakeTokensRegex, fakeTokensPrecedence);
  validateFiles("test-files/DigitOneTokenSpacesAndTabs_2.txt",
                propertiesFileName);
  std::vector<Token *> realTokens = ProductionParser::loadLexicalRules(
      "test-files/DigitOneTokenSpacesAndTabs_2.txt", propertiesFileName);
  testProductions(realTokens, fakeTokens);
}

TEST_F(TestParser, PunctuationsTokensSPacesAndTabs_3) {
  std::vector<std::string> fakeTokensType, fakeTokensRegex;
  std::vector<int> fakeTokensPrecedence;
  std::set<std::string> puncs;
  puncs.insert(";"), puncs.insert("["), puncs.insert("]"), puncs.insert("(");
  puncs.insert(")"), puncs.insert(","), puncs.insert("{"), puncs.insert("}");
  std::set<std::string>::iterator puncIter = puncs.begin();
  while (puncIter != puncs.end()) {
    addTokenToList(*puncIter, *puncIter, PUNCTUATION_PRIORITY, fakeTokensType,
                   fakeTokensRegex, fakeTokensPrecedence);
    puncIter++;
  }
  std::vector<Token *> fakeTokens =
      buildTokens(fakeTokensType, fakeTokensRegex, fakeTokensPrecedence);
  validateFiles("test-files/PunctuationsTokensSPacesAndTabs_3.txt",
                propertiesFileName);
  std::vector<Token *> realTokens = ProductionParser::loadLexicalRules(
      "test-files/PunctuationsTokensSPacesAndTabs_3.txt", propertiesFileName);
  testProductions(realTokens, fakeTokens);
}

TEST_F(TestParser, ReservedWordsSpacesAndTabs_4) {
  std::vector<std::string> fakeTokensType, fakeTokensRegex;
  std::vector<int> fakeTokensPrecedence;
  std::set<std::pair<std::string, std::string>> words;
  words.insert({"int", "in#t#"}), words.insert({"short", "sh#o#r#t#"});
  words.insert({"double", "do#u#b#l#e#"}), words.insert({"float", "fl#o#a#t#"});
  words.insert({"public", "pu#b#l#i#c#"});
  words.insert({"class", "cl#a#s#s#"});
  for (std::set<std::pair<std::string, std::string>>::iterator it =
           words.begin();
       it != words.end(); it++) {
    addTokenToList((*it).first, (*it).second, RESERVED_WORD_PRIORITY,
                   fakeTokensType, fakeTokensRegex, fakeTokensPrecedence);
  }
  std::vector<Token *> fakeTokens =
      buildTokens(fakeTokensType, fakeTokensRegex, fakeTokensPrecedence);
  validateFiles("test-files/ReservedWordsSpacesAndTabs_4.txt",
                propertiesFileName);
  std::vector<Token *> realTokens = ProductionParser::loadLexicalRules(
      "test-files/ReservedWordsSpacesAndTabs_4.txt", propertiesFileName);
  testProductions(realTokens, fakeTokens);
}

TEST_F(TestParser, SubstitutionWithRegularDefinition_5) {
  std::vector<std::string> fakeTokensType, fakeTokensRegex;
  std::vector<int> fakeTokensPrecedence;
  fakeTokensType.push_back("id");
  std::string regex = "a" + getRange('b', 'z') + ProductionParser::OR +
                      getRange('A', 'Z') + ProductionParser::OR;
  regex = regex + regex + "0" + getRange('1', '9') + ProductionParser::OR +
          ProductionParser::OR + ProductionParser::STAR +
          ProductionParser::CONCATENATE;
  fakeTokensRegex.push_back(regex);
  fakeTokensPrecedence.push_back(DEFAULT_PRIORITY - 2);
  std::vector<Token *> fakeTokens =
      buildTokens(fakeTokensType, fakeTokensRegex, fakeTokensPrecedence);
  validateFiles("test-files/SubstitutionWithRegularDefinition_5.txt",
                propertiesFileName);
  std::vector<Token *> realTokens = ProductionParser::loadLexicalRules(
      "test-files/SubstitutionWithRegularDefinition_5.txt", propertiesFileName);
  testProductions(realTokens, fakeTokens);
}

TEST_F(TestParser, OperatorConcatenateTestHard_6) {
  std::vector<RegexChar *> v;
  v.push_back(ProductionParser::makeRegexChar('T', CHAR));
  v.push_back(ProductionParser::makeRegexChar('#', CHAR));
  v.push_back(ProductionParser::makeRegexChar(CONCATENATE, OPERATOR));
  v.push_back(ProductionParser::makeRegexChar('h', CHAR));
  v.push_back(ProductionParser::makeRegexChar(CONCATENATE, OPERATOR));
  v.push_back(ProductionParser::makeRegexChar('#', CHAR));
  v.push_back(ProductionParser::makeRegexChar(CONCATENATE, OPERATOR));
  v.push_back(ProductionParser::makeRegexChar('i', CHAR));
  v.push_back(ProductionParser::makeRegexChar(CONCATENATE, OPERATOR));
  v.push_back(ProductionParser::makeRegexChar('#', CHAR));
  v.push_back(ProductionParser::makeRegexChar(CONCATENATE, OPERATOR));
  v.push_back(ProductionParser::makeRegexChar('s', CHAR));
  v.push_back(ProductionParser::makeRegexChar(CONCATENATE, OPERATOR));
  Token *fakeToken = new Token("concatenate", v, DEFAULT_PRIORITY);
  std::vector<Token *> fakeTokens;
  fakeTokens.push_back(fakeToken);
  validateFiles("test-files/OperatorConcatenateTestHard_6.txt",
                propertiesFileName);
  std::vector<Token *> realTokens = ProductionParser::loadLexicalRules(
      "test-files/OperatorConcatenateTestHard_6.txt", propertiesFileName);
  testProductions(realTokens, fakeTokens);
}

TEST_F(TestParser, NoMatchEmptyTokens_7) {
  std::vector<Token *> fakeTokens;
  validateFiles("test-files/NoMatchEmptyTokens_7.txt", propertiesFileName);
  std::vector<Token *> realTokens = ProductionParser::loadLexicalRules(
      "test-files/NoMatchEmptyTokens_7.txt", propertiesFileName);
  testProductions(realTokens, fakeTokens);
}

void validateFiles(std::string f1, std::string f2) {
  std::ifstream file1(f1.c_str());
  std::ifstream file2(f2.c_str());
  ASSERT_TRUE(file1 != NULL) << FILE_NOT_FOUND;
  ASSERT_TRUE(file2 != NULL) << FILE_NOT_FOUND;
}

void testProductions(std::vector<Token *> realTokens,
                     std::vector<Token *> fakeTokens) {
  ASSERT_TRUE(realTokens.size() == fakeTokens.size());
  for (int i = 0; i < realTokens.size(); i++) {
    EXPECT_EQ(fakeTokens[i]->getType(), realTokens[i]->getType());
    EXPECT_EQ(fakeTokens[i]->getPriority(), realTokens[i]->getPriority());
    ASSERT_TRUE(realTokens[i]->getPostfixRegix().size() ==
                fakeTokens[i]->getPostfixRegix().size());
    for (int j = 0; j < realTokens[i]->getPostfixRegix().size(); j++) {
      EXPECT_EQ(realTokens[i]->getPostfixRegix()[j]->c,
                fakeTokens[i]->getPostfixRegix()[j]->c);
      EXPECT_EQ(realTokens[i]->getPostfixRegix()[j]->charType,
                fakeTokens[i]->getPostfixRegix()[j]->charType);
    }
    delete realTokens[i];
    delete fakeTokens[i];
  }
}
