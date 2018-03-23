#include "RegexToNfaConverter.hpp"

NFA *RegexToNfaConverter::getNfa(std::vector<Token *> tokens) {
  std::pair<int, int> range = getAsciiRange(tokens);
  NFA *nfa = new NFA(range.first, range.second);
  stateID rootID = nfa->createNode();
  for (int i = 0; i < tokens.size(); i++) {
    if (validatePostfix(tokens[i])) {
      struct SubNfa *tokenNfa = convertToken(tokens[i], nfa);
      if (tokenNfa)
        nfa->addTransition(EPS_TRANS, rootID, tokenNfa->startID);
      delete tokenNfa;
    } else {
      std::cout << "ERROR expression" << std::endl;
    }
  }
  return nfa;
}

struct SubNfa *RegexToNfaConverter::convertToken(Token *token, NFA *nfa) {
  std::stack<struct SubNfa *> nfaStack;
  std::vector<RegexChar *> postfixRegex = token->getPostfixRegix();
  std::vector<stateID> createdNodes;
  for (int i = 0; i < (int)postfixRegex.size(); i++) {
    if (isBinaryOperation(postfixRegex[i])) {
      doBinaryOperation(nfaStack, nfa, postfixRegex[i]->c, createdNodes);
    } else if (isUnaryOperation(postfixRegex[i])) {
      doUnaryOperation(nfaStack, nfa, postfixRegex[i]->c, createdNodes);
    } else {
      nfaStack.push(buildChar(postfixRegex[i]->c, nfa, createdNodes));
    }
  }
  if ((int)nfaStack.size() != 1) {
    return NULL;
  }
  struct SubNfa *totalNfaToken = nfaStack.top();
  nfaStack.pop();
  nfa->setStateSpec(totalNfaToken->endID, token->getPriority(),
                    token->getType(), ACCEPTED);
  return totalNfaToken;
}

void RegexToNfaConverter::doBinaryOperation(
    std::stack<struct SubNfa *> &nfaStack, NFA *nfa, char operation,
    std::vector<stateID> &createdNodes) {
  if (nfaStack.size() < 2) {
    return;
  }
  struct SubNfa *secondNfa = nfaStack.top();
  nfaStack.pop();
  struct SubNfa *firstNfa = nfaStack.top();
  nfaStack.pop();
  struct SubNfa *finalNfa;
  switch (operation) {
  case OR_OP:
    finalNfa = buildOr(firstNfa, secondNfa, nfa, createdNodes);
    break;
  case CONC_OP:
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
    std::stack<struct SubNfa *> &nfaStack, NFA *nfa, char operation,
    std::vector<stateID> &createdNodes) {
  if (nfaStack.empty()) {
    return;
  }
  struct SubNfa *subNfa = nfaStack.top();
  nfaStack.pop();
  struct SubNfa *finalNfa;
  switch (operation) {
  case STAR_OP:
    finalNfa = buildStar(subNfa, nfa, createdNodes);
    break;
  case PLUS_OP:
    finalNfa = buildPlus(subNfa, nfa, createdNodes);
    break;
  default:
    finalNfa = buildChar(operation, nfa, createdNodes);
    break;
  }
  nfaStack.push(finalNfa);
  delete subNfa;
}

struct SubNfa *
RegexToNfaConverter::buildChar(char transition, NFA *nfa,
                               std::vector<stateID> &createdNodes) {
  stateID startID = nfa->createNode();
  stateID endID = nfa->createNode();
  createdNodes.push_back(startID);
  createdNodes.push_back(endID);
  nfa->addTransition(transition, startID, endID);
  return createSubNfa(startID, endID);
}

struct SubNfa *RegexToNfaConverter::buildConcatenate(struct SubNfa *firstNfa,
                                                     struct SubNfa *secondNfa,
                                                     NFA *nfa) {
  nfa->addTransition(EPS_TRANS, firstNfa->endID, secondNfa->startID);
  return createSubNfa(firstNfa->startID, secondNfa->endID);
}

struct SubNfa *
RegexToNfaConverter::buildOr(struct SubNfa *firstNfa, struct SubNfa *secondNfa,
                             NFA *nfa, std::vector<stateID> &createdNodes) {
  stateID startID = nfa->createNode();
  stateID endID = nfa->createNode();
  createdNodes.push_back(startID);
  createdNodes.push_back(endID);
  nfa->addTransition(EPS_TRANS, startID, firstNfa->startID);
  nfa->addTransition(EPS_TRANS, startID, secondNfa->startID);
  nfa->addTransition(EPS_TRANS, firstNfa->endID, endID);
  nfa->addTransition(EPS_TRANS, secondNfa->endID, endID);
  return createSubNfa(startID, endID);
}

struct SubNfa *
RegexToNfaConverter::buildStar(struct SubNfa *subNfa, NFA *nfa,
                               std::vector<stateID> &createdNodes) {
  stateID startID = nfa->createNode();
  stateID endID = nfa->createNode();
  createdNodes.push_back(startID);
  createdNodes.push_back(endID);
  nfa->addTransition(EPS_TRANS, startID, subNfa->startID);
  nfa->addTransition(EPS_TRANS, startID, endID);
  nfa->addTransition(EPS_TRANS, subNfa->endID, endID);
  nfa->addTransition(EPS_TRANS, subNfa->endID, subNfa->startID);
  return createSubNfa(startID, endID);
}

struct SubNfa *
RegexToNfaConverter::buildPlus(struct SubNfa *subNfa, NFA *nfa,
                               std::vector<stateID> &createdNodes) {
  stateID endID = nfa->createNode();
  createdNodes.push_back(endID);
  nfa->addTransition(EPS_TRANS, subNfa->endID, endID);
  nfa->addTransition(EPS_TRANS, subNfa->endID, subNfa->startID);
  return createSubNfa(subNfa->startID, endID);
}

struct SubNfa *RegexToNfaConverter::createSubNfa(stateID startID,
                                                 stateID endID) {
  struct SubNfa *subNfa = new SubNfa;
  subNfa->startID = startID;
  subNfa->endID = endID;
  return subNfa;
}

bool RegexToNfaConverter::isBinaryOperation(RegexChar *regexChar) {
  return regexChar->charType == OPERATOR &&
         (regexChar->c == OR_OP || regexChar->c == CONC_OP);
}

bool RegexToNfaConverter::isUnaryOperation(RegexChar *regexChar) {
  return regexChar->charType == OPERATOR &&
         (regexChar->c == STAR_OP || regexChar->c == PLUS_OP);
}

bool RegexToNfaConverter::validatePostfix(Token *token) {
  int stackArgs = 0;
  for (int i = 0; i < token->getPostfixRegix().size(); i++) {
    if (isBinaryOperation(token->getPostfixRegix()[i])) {
      stackArgs--;
    } else if (!isUnaryOperation(token->getPostfixRegix()[i])) {
      stackArgs++;
    }
  }
  return stackArgs == 1;
}

std::pair<int, int>
RegexToNfaConverter::getAsciiRange(std::vector<Token *> tokens) {
  std::pair<int, int> range = {EPS_TRANS, EPS_TRANS};
  for (int i = 0; i < tokens.size(); i++) {
    for (int j = 0; j < tokens[i]->getPostfixRegix().size(); j++) {
      range.first =
          std::min(range.first, (int)tokens[i]->getPostfixRegix()[j]->c);
      range.second =
          std::max(range.second, (int)tokens[i]->getPostfixRegix()[j]->c);
    }
  }
  return range;
}
