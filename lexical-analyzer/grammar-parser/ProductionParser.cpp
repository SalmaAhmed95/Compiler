#include "ProductionParser.hpp"

/* Properies file key data. */
std::string ProductionParser::REG_DEF_EQU = "regular_def_equ";
std::string ProductionParser::REG_EXP_EQU = "regular_exp_equ";
std::string ProductionParser::START_RESERVED_ENCLOSING =
    "start_reserverd_enclosing";
std::string ProductionParser::END_RESERVED_ENCLOSING = "end_reserved_enclosing";
std::string ProductionParser::START_PUNC_ENLCOSING =
    "start_punctuation_enclosing";
std::string ProductionParser::END_PUNC_ENCLOSING = "end_punctuation_enclosing";
std::string ProductionParser::LAMBDA = "lambda_symbol";

const char ProductionParser::CONCATENATE = '#';
const char ProductionParser::OR = '|';
const char ProductionParser::STAR = '*';
const char ProductionParser::PLUS = '+';
const char ProductionParser::BRACKET_OPEN = '(';
const char ProductionParser::BRACKET_CLOSE = ')';

const char ProductionParser::EPS = '`';

std::map<char, int> ProductionParser::precedence;

struct RegexChar *ProductionParser::makeRegexChar(char c,
                                                  TokenCharType charType) {
  struct RegexChar *regexChar = new RegexChar;
  regexChar->c = c;
  regexChar->charType = charType;
}

ProductionParser::ProductionParser() {}

std::vector<Token *>
ProductionParser::loadLexicalRules(std::string lexicalRulesFileName,
                                   std::string propertiesFileName) {

  loadPrecedence();
  int priority = DEFAULT_PRIORITY;
  std::map<std::string, std::string> variables;
  Properties::PropertiesData propertiesData;
  loadProperties(propertiesFileName, propertiesData);
  std::vector<Token *> formulatedTokens;
  std::ifstream lexicalRules(lexicalRulesFileName.c_str());
  handleFileNotFound(lexicalRules);
  std::string inputRuleLine;
  while (getline(lexicalRules, inputRuleLine)) {
    inputRuleLine = trim(inputRuleLine, " \t");
    if (!inputRuleLine.empty()) {
      processLine(inputRuleLine, formulatedTokens, propertiesData, variables,
                  priority);
    }
    priority--;
  }
  return formulatedTokens;
}

void ProductionParser::loadPrecedence() {
  precedence[BRACKET_OPEN] = BRACKET_PREC;
  precedence[OR] = OR_PREC;
  precedence[CONCATENATE] = CONCATENATE_PREC;
  precedence[STAR] = STAR_PREC;
  precedence[PLUS] = PLUS_PREC;
}

void ProductionParser::processLine(
    std::string line, std::vector<Token *> &tokens,
    Properties::PropertiesData propertiesData,
    std::map<std::string, std::string> &variables, int priority) {
  if (isReservedWord(line, propertiesData)) {
    processReservedWord(line, tokens);
  } else if (isPunctuation(line, propertiesData)) {
    processPunctuation(line, tokens);
  } else if (isRegularDefinition(line, propertiesData)) {
    processRegularDefinition(line, variables, propertiesData);
  } else if (isRegularExpression(line, propertiesData)) {
    processRegularExpression(line, tokens, priority, variables, propertiesData);
  } else {
    std::cout << "No match for lexical rules" << '\n';
  }
}

void ProductionParser::processRegularExpression(
    std::string line, std::vector<Token *> &tokens, int priority,
    std::map<std::string, std::string> &variables,
    Properties::PropertiesData properties) {
  int firstOcc = line.find(properties.find(REG_EXP_EQU)->second[0]);
  std::string tokenType = formulateSpaces(line.substr(0, firstOcc), "", " \t");
  std::string regex = line.substr(firstOcc + 1);
  if (variables.count(tokenType)) {
    return;
  }
  regex = substituteVariables(regex, variables);
  regex = formulateSpaces(regex, "", " \t");
  regex = substituteRanges(regex);
  char lambda = 0;
  if (properties.find(LAMBDA) != properties.end() &&
      properties.find(LAMBDA)->second.size() == 2) {
    lambda = properties.find(LAMBDA)->second[1];
  }
  tokens.push_back(new Token(tokenType, getPostfix(regex, lambda), priority));
}

void ProductionParser::processRegularDefinition(
    std::string line, std::map<std::string, std::string> &variables,
    Properties::PropertiesData properties) {
  int firstOcc = line.find(properties.find(REG_DEF_EQU)->second[0]);
  std::string variableName =
      formulateSpaces(line.substr(0, firstOcc), "", " \t");
  std::string regex = line.substr(firstOcc + 1);
  if (variables.count(variableName)) {
    return;
  }
  regex = substituteVariables(regex, variables);
  regex = formulateSpaces(regex, "", " \t");
  variables[variableName] = substituteRanges(regex);
}

std::string ProductionParser::substituteVariables(
    std::string regex, std::map<std::string, std::string> &variables) {
  std::string substitutedString = "";
  for (int i = 0; i < (int)regex.size(); i++) {
    std::string variable = "";
    while (i < (int)regex.size() && (isalpha(regex[i]) || isdigit(regex[i]))) {
      variable = variable + regex[i];
      i++;
    }
    if (variable.empty()) {
      substitutedString = substitutedString + regex[i];
    } else if (variables.count(variable)) {
      substitutedString = substitutedString + BRACKET_OPEN +
                          variables.find(variable)->second + BRACKET_CLOSE;
      i--;
    } else {
      substitutedString = substitutedString + variable;
      i--;
    }
  }
  return substitutedString;
}

bool ProductionParser::isRange(std::string str, int ind) {
  return ind + 2 < (int)str.size() && str[ind + 1] == '-' &&
         ((isalpha(str[ind]) && isalpha(str[ind + 2])) ||
          (isdigit(str[ind]) && isdigit(str[ind + 2])));
}

std::string ProductionParser::substituteRanges(std::string regex) {
  std::string substitutedString = "";
  for (int i = 0; i < (int)regex.size(); i++) {
    if (isRange(regex, i)) {
      char beg = regex[i], en = regex[i + 2];
      std::string range = "";
      while (beg <= en) {
        range = range + (char)beg;
        range = range + (beg != en ? "|" : "");
        beg++;
      }
      substitutedString = substitutedString + range;
      i += 2;
    } else {
      substitutedString = substitutedString + regex[i];
    }
  }
  return substitutedString;
}

void ProductionParser::processPunctuation(std::string line,
                                          std::vector<Token *> &tokens) {
  line = formulateSpaces(line, "", " \t");
  std::set<std::string> punctuations;
  for (int i = 1; i < (int)line.size() - 1;) {
    i += line[i] == '\\';
    if (i < (int)line.size() - 1) {
      punctuations.insert(std::string(1, line[i]));
    }
    i++;
  }
  std::set<std::string>::iterator puncIter = punctuations.begin();
  while (puncIter != punctuations.end()) {
    std::vector<RegexChar *> v;
    v.push_back(makeRegexChar((*puncIter)[0], CHAR));
    Token *puncToken = new Token(*puncIter, v, PUNCTUATION_PRIORITY);
    tokens.push_back(puncToken);
    puncIter++;
  }
}

void ProductionParser::processReservedWord(std::string line,
                                           std::vector<Token *> &tokens) {
  line = formulateSpaces(line, " ", " \t");
  std::string currentWord;
  std::set<std::string> reservedWords;
  for (int i = 1; i < (int)line.size() - 1; i++) {
    if (line[i] == ' ') {
      if (!currentWord.empty()) {
        reservedWords.insert(currentWord);
      }
      currentWord = "";
    } else {
      currentWord = currentWord + line[i];
    }
  }
  if (!currentWord.empty()) {
    reservedWords.insert(currentWord);
  }
  std::set<std::string>::iterator reservedIter = reservedWords.begin();
  while (reservedIter != reservedWords.end()) {
    Token *reservedToken = new Token(
        *reservedIter, getPostfix(*reservedIter, 0), RESERVED_WORD_PRIORITY);
    tokens.push_back(reservedToken);
    reservedIter++;
  }
}

bool ProductionParser::isReservedWord(
    std::string line, Properties::PropertiesData propertiesData) {
  return propertiesData.find(START_RESERVED_ENCLOSING) !=
             propertiesData.end() &&
         propertiesData.find(END_RESERVED_ENCLOSING) != propertiesData.end() &&
         std::string(1, line[0]) ==
             propertiesData.find(START_RESERVED_ENCLOSING)->second &&
         std::string(1, line[(int)line.size() - 1]) ==
             propertiesData.find(END_RESERVED_ENCLOSING)->second;
}

bool ProductionParser::isPunctuation(
    std::string line, Properties::PropertiesData propertiesData) {
  return propertiesData.find(START_PUNC_ENLCOSING) != propertiesData.end() &&
         propertiesData.find(END_PUNC_ENCLOSING) != propertiesData.end() &&
         std::string(1, line[0]) ==
             propertiesData.find(START_PUNC_ENLCOSING)->second &&
         std::string(1, line[(int)line.size() - 1]) ==
             propertiesData.find(END_PUNC_ENCLOSING)->second;
}

bool ProductionParser::isRegularDefinition(
    std::string line, Properties::PropertiesData propertiesData) {
  if (!isalpha(line[0])) {
    return false;
  }
  std::string str = formulateSpaces(line, "", " \t");
  for (int i = 1; i < (int)str.size(); i++) {
    if (!isalpha(str[i]) && !isdigit(str[i])) {
      return propertiesData.find(REG_DEF_EQU) != propertiesData.end() &&
             std::string(1, str[i]) == propertiesData.find(REG_DEF_EQU)->second;
    }
  }
  return false;
}

bool ProductionParser::isRegularExpression(
    std::string line, Properties::PropertiesData propertiesData) {
  if (!isalpha(line[0])) {
    return false;
  }
  std::string str = formulateSpaces(line, "", " \t");
  for (int i = 1; i < (int)str.size(); i++) {
    if (!isalpha(str[i]) && !isdigit(str[i])) {
      return propertiesData.find(REG_EXP_EQU) != propertiesData.end() &&
             std::string(1, str[i]) == propertiesData.find(REG_EXP_EQU)->second;
    }
  }
  return false;
}

std::string ProductionParser::preprocessInfix(std::string infix) {
  std::string modifiedInfix = "";
  for (int i = 0; i < (int)infix.size(); i++) {
    char c1 = infix[i];
    if (i + 1 < (int)infix.size()) {
      char c2 = infix[i + 1];
      modifiedInfix = modifiedInfix + c1 + "";
      if (c1 != '(' && c2 != ')' && (!precedence.count(c2) || c2 == '(') &&
          c1 != OR && c1 != '\\') {
        modifiedInfix = modifiedInfix + CONCATENATE + "";
      }
      if (c1 != '(' && c2 != ')' && c2 == CONCATENATE && c1 != OR &&
          c1 != '\\') {
        modifiedInfix = modifiedInfix + CONCATENATE + "\\";
      }
    }
  }
  modifiedInfix = modifiedInfix + infix[(int)infix.size() - 1] + "";
  return modifiedInfix;
}

int ProductionParser::getPrecedence(const char c, TokenCharType charType) {
  return ((charType == CHAR || !precedence.count(c)) ? DEFAULT_PREC
                                                     : precedence[c]);
}

std::vector<RegexChar *> ProductionParser::getPostfix(std::string infix,
                                                      char lambda) {
  infix = preprocessInfix(infix);
  std::vector<RegexChar *> postfixRegex;
  std::stack<char> postfixStack;
  std::stack<TokenCharType> skip;
  for (int i = 0; i < (int)infix.size(); i++) {
    TokenCharType charType = infix[i] == '\\' ? CHAR : DEFAULT_TYPE;
    i += charType == CHAR;
    char currChar = infix[i] == lambda && charType == CHAR ? EPS : infix[i];
    if (i >= (int)infix.size()) {
      return postfixRegex;
    }
    if (currChar == BRACKET_OPEN && charType == DEFAULT_TYPE) {
      postfixStack.push(currChar);
      skip.push(charType);
    } else if (currChar == BRACKET_CLOSE && charType == DEFAULT_TYPE) {
      while (postfixStack.size() > 0 && postfixStack.top() != BRACKET_OPEN) {
        postfixRegex.push_back(makeRegexChar(postfixStack.top(), skip.top()));
        postfixStack.pop();
        skip.pop();
      }
      postfixStack.pop();
      skip.pop();
    } else {
      bool stop = false;
      while ((int)postfixStack.size() > 0 && !stop) {
        char c = postfixStack.top();
        TokenCharType opSkip = skip.top();
        if (getPrecedence(c, opSkip) >= getPrecedence(currChar, charType)) {
          postfixRegex.push_back(makeRegexChar(postfixStack.top(), skip.top()));
          postfixStack.pop();
          skip.pop();
        } else {
          stop = true;
        }
      }
      postfixStack.push(currChar);
      skip.push(charType == CHAR || !precedence.count(currChar) ? CHAR
                                                                : OPERATOR);
    }
  }
  while (!postfixStack.empty()) {
    postfixRegex.push_back(makeRegexChar(postfixStack.top(), skip.top()));
    postfixStack.pop();
    skip.pop();
  }
  return postfixRegex;
}

std::string ProductionParser::trim(std::string str, std::string whitespace) {
  const int strBegin = str.find_first_not_of(whitespace);
  if (strBegin == std::string::npos) {
    return "";
  }
  const int strEnd = str.find_last_not_of(whitespace);
  const int strRange = strEnd - strBegin + 1;
  return str.substr(strBegin, strRange);
}

std::string ProductionParser::formulateSpaces(std::string str, std::string fill,
                                              std::string whitespace) {
  std::string result = trim(str, whitespace);
  int beginSpace = result.find_first_of(whitespace);
  while (beginSpace != std::string::npos) {
    const int endSpace = result.find_first_not_of(whitespace, beginSpace);
    const int range = endSpace - beginSpace;
    result.replace(beginSpace, range, fill);
    const int newStart = beginSpace + fill.length();
    beginSpace = result.find_first_of(whitespace, newStart);
  }

  return result;
}

void ProductionParser::loadProperties(
    std::string propertiesFileName,
    Properties::PropertiesData &propertiesData) {
  std::ifstream propertiesFile(propertiesFileName.c_str());
  handleFileNotFound(propertiesFile);
  propertiesFile >> propertiesData;
}

void ProductionParser::handleFileNotFound(std::ifstream &file) {
  if (!file) {
    std::cout << "File not found" << std::endl;
    exit(0);
  }
}

ProductionParser::~ProductionParser() {}
