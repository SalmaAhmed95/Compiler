#include "RegexToNfaConverter.hpp"

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
