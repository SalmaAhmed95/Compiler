#include "RegexToNfaConverter.hpp"

NFA *RegexToNfaConverter::getNfa(std::vector<Token *> tokens) {
  NFA *nfa = new NFA();
  stateID rootID = nfa->createNode();
  std::vector<struct SubNfa *> allNfa;
  for (int i = 0; i < tokens.size(); i++) {
    struct SubNfa *tokenNfa = convertToken(tokens[i], nfa);
    nfa->addTransition(EPS, rootID, tokenNfa->startID);
    delete tokenNfa;
  }
  return nfa;
}

struct SubNfa *RegexToNfaConverter::convertToken(Token *token, NFA *nfa) {
  std::stack<struct SubNfa *> nfaStack;
  std::string postfixRegex = token->getPostfixRegix();
  for (int i = 0; i < (int)postfixRegex.size(); i++) {
    if (isBinaryOperation(postfixRegex[i])) {
      doBinaryOperation(nfaStack, nfa, postfixRegex[i]);
    } else {
      doUnaryOperation(nfaStack, nfa, postfixRegex[i]);
    }
  }
  if ((int)nfaStack.size() > 1) {
    return NULL;
  }
  struct SubNfa *totalNfaToken = nfaStack.top();
  nfaStack.pop();
  struct AcceptanceSpec *acceptanceSpec = new AcceptanceSpec;
  acceptanceSpec->precedence = token->getPriority();
  acceptanceSpec->type = token->getType();
  nfa->setAcceptance(totalNfaToken->endID, acceptanceSpec);
  return totalNfaToken;
}

void RegexToNfaConverter::doBinaryOperation(
    std::stack<struct SubNfa *> &nfaStack, NFA *nfa, char operation) {
  if (nfaStack.size() < 2) {
    return;
  }
  struct SubNfa *secondNfa = nfaStack.top();
  nfaStack.pop();
  struct SubNfa *firstNfa = nfaStack.top();
  nfaStack.pop();
  struct SubNfa *finalNfa;
  switch (operation) {
  case '|':
    finalNfa = buildOr(firstNfa, secondNfa, nfa);
    break;
  case '#':
    finalNfa = buildConcatenate(firstNfa, secondNfa, nfa);
    break;
  default:
    break;
  }
  nfaStack.push(finalNfa);
  delete firstNfa;
  delete secondNfa;
}

void RegexToNfaConverter::doUnaryOperation(
    std::stack<struct SubNfa *> &nfaStack, NFA *nfa, char operation) {
  if (nfaStack.empty()) {
    return;
  }
  struct SubNfa *subNfa = nfaStack.top();
  nfaStack.pop();
  struct SubNfa *finalNfa;
  switch (operation) {
  case '*':
    finalNfa = buildStar(subNfa, nfa);
    break;
  case '+':
    finalNfa = buildPlus(subNfa, nfa);
    break;
  default:
    finalNfa = buildChar(operation, nfa);
    break;
  }
  nfaStack.push(finalNfa);
  delete subNfa;
}

struct SubNfa *RegexToNfaConverter::buildChar(char transition, NFA *nfa) {
  stateID startID = nfa->createNode();
  stateID endID = nfa->createNode();
  nfa->addTransition(transition, startID, endID);
  return createSubNfa(startID, endID);
}

struct SubNfa *RegexToNfaConverter::buildConcatenate(struct SubNfa *firstNfa,
                                                     struct SubNfa *secondNfa,
                                                     NFA *nfa) {
  nfa->addTransition(EPS, firstNfa->endID, secondNfa->startID);
  return createSubNfa(firstNfa->startID, secondNfa->endID);
}

struct SubNfa *RegexToNfaConverter::buildOr(struct SubNfa *firstNfa,
                                            struct SubNfa *secondNfa,
                                            NFA *nfa) {
  stateID startID = nfa->createNode();
  stateID endID = nfa->createNode();
  nfa->addTransition(EPS, startID, firstNfa->startID);
  nfa->addTransition(EPS, startID, secondNfa->startID);
  nfa->addTransition(EPS, firstNfa->endID, endID);
  nfa->addTransition(EPS, secondNfa->endID, endID);
  return createSubNfa(startID, endID);
}

struct SubNfa *RegexToNfaConverter::buildStar(struct SubNfa *subNfa, NFA *nfa) {
  stateID startID = nfa->createNode();
  stateID endID = nfa->createNode();
  nfa->addTransition(EPS, startID, subNfa->startID);
  nfa->addTransition(EPS, startID, endID);
  nfa->addTransition(EPS, subNfa->endID, endID);
  nfa->addTransition(EPS, subNfa->endID, subNfa->startID);
  return createSubNfa(startID, endID);
}

struct SubNfa *RegexToNfaConverter::buildPlus(struct SubNfa *subNfa, NFA *nfa) {
  stateID endID = nfa->createNode();
  nfa->addTransition(EPS, subNfa->endID, endID);
  nfa->addTransition(EPS, subNfa->endID, subNfa->startID);
  return createSubNfa(subNfa->startID, endID);
}

struct SubNfa *RegexToNfaConverter::createSubNfa(stateID startID,
                                                 stateID endID) {
  struct SubNfa *subNfa = new SubNfa;
  subNfa->startID = startID;
  subNfa->endID = endID;
  return subNfa;
}

bool RegexToNfaConverter::isBinaryOperation(char operation) {
  return operation == '|' || operation == '#';
}
