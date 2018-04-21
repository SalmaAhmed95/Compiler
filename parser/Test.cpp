//#include "Grammar.h"
//
////
//// Created by salma on 19/04/18.
////
//int main(int argc, char **argv) {
//
//    Grammar *grammar = new Grammar();
//    std::vector<Production> rhs;
//    std::vector<Symbol> symbols;
//    symbols.push_back(Symbol("T",NON_TERMINAL));
//    symbols.push_back(Symbol("E`",NON_TERMINAL));
//    Production P1;
//    P1.production = symbols;
//    rhs.push_back(P1);
//    grammar->productions.insert(std::pair<Symbol,std::vector<Production>>(Symbol("E",START),rhs));
//
//    rhs.clear();
//    symbols.clear();
//    symbols.push_back(Symbol("+",TERMINAL));
//    symbols.push_back(Symbol("E",START));
//    P1.production = symbols;
//    rhs.push_back(P1);
//    symbols.clear();
//    symbols.push_back(Symbol(EPSILONSYMBOl,EPSILON));
//    P1.production = symbols;
//    rhs.push_back(P1);
//    grammar->productions.insert(std::pair<Symbol,std::vector<Production>>(Symbol("E`",NON_TERMINAL),rhs));
//
//    rhs.clear();
//    symbols.clear();
//    symbols.push_back(Symbol("F",NON_TERMINAL));
//    symbols.push_back(Symbol("T`",NON_TERMINAL));
//    P1.production = symbols;
//    rhs.push_back(P1);
//    grammar->productions.insert(std::pair<Symbol,std::vector<Production>>(Symbol("T",NON_TERMINAL),rhs));
//
//
//    rhs.clear();
//    symbols.clear();
//    symbols.push_back(Symbol("T",NON_TERMINAL));
//    P1.production = symbols;
//    rhs.push_back(P1);
//    symbols.clear();
//    symbols.push_back(Symbol(EPSILONSYMBOl,EPSILON));
//    P1.production = symbols;
//    rhs.push_back(P1);
//    grammar->productions.insert(std::pair<Symbol,std::vector<Production>>(Symbol("T`",NON_TERMINAL),rhs));
//
//    rhs.clear();
//    symbols.clear();
//    symbols.push_back(Symbol("P",NON_TERMINAL));
//    symbols.push_back(Symbol("F`",NON_TERMINAL));
//    P1.production = symbols;
//    rhs.push_back(P1);
//    grammar->productions.insert(std::pair<Symbol,std::vector<Production>>(Symbol("F",NON_TERMINAL),rhs));
//
//    rhs.clear();
//    symbols.clear();
//    symbols.push_back(Symbol("*",TERMINAL));
//    symbols.push_back(Symbol("F",NON_TERMINAL));
//    P1.production = symbols;
//    rhs.push_back(P1);
//    symbols.clear();
//    symbols.push_back(Symbol(EPSILONSYMBOl,EPSILON));
//    P1.production = symbols;
//    rhs.push_back(P1);
//    grammar->productions.insert(std::pair<Symbol,std::vector<Production>>(Symbol("F`",NON_TERMINAL),rhs));
//
//    rhs.clear();
//    symbols.clear();
//    symbols.push_back(Symbol("(",TERMINAL));
//    symbols.push_back(Symbol("E",START));
//    symbols.push_back(Symbol(")",TERMINAL));
//    P1.production = symbols;
//    rhs.push_back(P1);
//    symbols.clear();
//    symbols.push_back(Symbol("a",TERMINAL));
//    P1.production = symbols;
//    rhs.push_back(P1);
//    symbols.clear();
//    symbols.push_back(Symbol("b",TERMINAL));
//    P1.production = symbols;
//    rhs.push_back(P1);
//    symbols.clear();
//    symbols.push_back(Symbol("Em",NON_TERMINAL));
//    P1.production = symbols;
//    rhs.push_back(P1);
//    grammar->productions.insert(std::pair<Symbol,std::vector<Production>>(Symbol("P",NON_TERMINAL),rhs));
//
//    std::set<Symbol>first ;
//    first.insert(Symbol("(",TERMINAL));
//    first.insert(Symbol("a",TERMINAL));
//    first.insert(Symbol("b",TERMINAL));
//    first.insert(Symbol("Em",NON_TERMINAL));
//    grammar->first.insert(std::pair<Symbol,std::set<Symbol>>(Symbol("E",START),first));
//
//    first.clear();
//    first.insert(Symbol("+",TERMINAL));
//    first.insert(Symbol(EPSILONSYMBOl,EPSILON));
//    grammar->first.insert(std::pair<Symbol,std::set<Symbol>>(Symbol("E`",NON_TERMINAL),first));
//
//    first.clear();
//    first.insert(Symbol("(",TERMINAL));
//    first.insert(Symbol("a",TERMINAL));
//    first.insert(Symbol("b",TERMINAL));
//    first.insert(Symbol("Em",NON_TERMINAL));
//    grammar->first.insert(std::pair<Symbol,std::set<Symbol>>(Symbol("T",NON_TERMINAL),first));
//
//
//    first.clear();
//    first.insert(Symbol("(",TERMINAL));
//    first.insert(Symbol("a",TERMINAL));
//    first.insert(Symbol("b",TERMINAL));
//    first.insert(Symbol("Em",NON_TERMINAL));
//    first.insert(Symbol(EPSILONSYMBOl,EPSILON));
//    grammar->first.insert(std::pair<Symbol,std::set<Symbol>>(Symbol("T`",NON_TERMINAL),first));
//
//    first.clear();
//    first.insert(Symbol("(",TERMINAL));
//    first.insert(Symbol("a",TERMINAL));
//    first.insert(Symbol("b",TERMINAL));
//    first.insert(Symbol("Em",NON_TERMINAL));
//    grammar->first.insert(std::pair<Symbol,std::set<Symbol>>(Symbol("F",NON_TERMINAL),first));
//
//    first.clear();
//    first.insert(Symbol("*",TERMINAL));
//    first.insert(Symbol(EPSILONSYMBOl,EPSILON));
//    grammar->first.insert(std::pair<Symbol,std::set<Symbol>>(Symbol("F`",NON_TERMINAL),first));
//
//    first.clear();
//    first.insert(Symbol("(",TERMINAL));
//    first.insert(Symbol("a",TERMINAL));
//    first.insert(Symbol("b",TERMINAL));
//    first.insert(Symbol("Em",NON_TERMINAL));
//    grammar->first.insert(std::pair<Symbol,std::set<Symbol>>(Symbol("P",NON_TERMINAL),first));
//
//     grammar->constructFollowSet();
//     grammar->printSets(grammar->follow);
//
//
//
//
//
//
//    return 0;
//}
