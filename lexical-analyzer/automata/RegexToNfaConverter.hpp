#include "../grammar-parser/Token.hpp"
#include "NFA.h"

#define EPS '`'

struct SubNfa {
  stateID startID;
  stateID endID;
};

class RegexToNfaConverter {
public:
  static NFA getNfa(std::vector<Token *> tokens);

private:
  RegexToNfaConverter();
  static struct SubNfa *buildChar(char transition, NFA *nfa);
  static struct SubNfa *buildConcatenate(struct SubNfa *firstNfa,
                                         struct SubNfa *secondNfa, NFA *nfa);
  static struct SubNfa *buildOr(struct SubNfa *firstNfa,
                                struct SubNfa *secondNfa, NFA *nfa);
  static struct SubNfa *buildStar(struct SubNfa *subNfa, NFA *nfa);
  static struct SubNfa *buildPlus(struct SubNfa *subNfa, NFA *nfa);

  static struct SubNfa *createSubNfa(stateID startID, stateID endID);
};
