#include "Properties.hpp"
#include "Token.hpp"
#include <ctype.h>
#include <map>
#include <set>
#include <stack>
#include <vector>

#define PUNCTUATION_PRIORITY 1e9
#define RESERVED_WORD_PRIORITY 1e9
#define DEFAULT_PRIORITY 1e5

class ProductionParser {
public:
  ProductionParser();
  static std::vector<Token *> loadLexicalRules(std::string lexicalRulesFileName,
                                               std::string propertiesFileName);
  virtual ~ProductionParser();

protected:
  static std::string removeSpaces(std::string str);
  static void processLine(std::string line, std::vector<Token *> &tokens,
                          Properties::PropertiesData propertiesData,
                          std::map<std::string, std::string> &variables,
                          int priority);
  static void processPunctuation(std::string line,
                                 std::vector<Token *> &tokens);
  static void processReservedWord(std::string line,
                                  std::vector<Token *> &tokens);
  static void
  processRegularExpression(std::string line, std::vector<Token *> &tokens,
                           int priority,
                           std::map<std::string, std::string> &variables,
                           Properties::PropertiesData properties);
  static void
  processRegularDefinition(std::string line,
                           std::map<std::string, std::string> &variables,
                           Properties::PropertiesData properties);
  static std::string
  substituteVariables(std::string regex,
                      std::map<std::string, std::string> &variables);
  static std::string substituteRanges(std::string regex);
  static bool isRange(std::string str, int ind);
  static bool isReservedWord(std::string line,
                             Properties::PropertiesData propertiesData);
  static bool isPunctuation(std::string line,
                            Properties::PropertiesData propertiesData);
  static bool isRegularDefinition(std::string line,
                                  Properties::PropertiesData propertiesData);
  static bool isRegularExpression(std::string line,
                                  Properties::PropertiesData propertiesData);
  static std::vector<RegexChar *> getPostfix(std::string infix, char lambda);
  static std::string preprocessInfix(std::string infix);
  static int getPrecedence(const char c, TokenCharType charType);
  static void
  loadProperties(std::string propertiesFileName, Properties::PropertiesData &propertiesData);
  static void loadPrecedence();
  static std::string trim(std::string str, std::string whitespace);
  static std::string formulateSpaces(std::string str, std::string fill,
                                     std::string whitespace);
  static struct RegexChar *makeRegexChar(char c, TokenCharType charType);
    static void handleFileNotFound(std::ifstream &file);

  /* Properies file key data. */
  static std::string REG_DEF_EQU;
  static std::string REG_EXP_EQU;
  static std::string START_RESERVED_ENCLOSING;
  static std::string END_RESERVED_ENCLOSING;
  static std::string START_PUNC_ENLCOSING;
  static std::string END_PUNC_ENCLOSING;
  static std::string LAMBDA;

  static const char CONCATENATE;
  static const char OR;
  static const char STAR;
  static const char PLUS;
  static const char BRACKET_OPEN;
  static const char BRACKET_CLOSE;

  static const char EPS;

  static std::map<char, int> precedence;

  enum OperatorsPrecedence {
    BRACKET_PREC,
    OR_PREC,
    CONCATENATE_PREC,
    STAR_PREC,
    PLUS_PREC,
    DEFAULT_PREC
  };
};
