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
//    rhs.push_back(Production(symbols));
//    grammar->productions.insert(std::pair<Symbol,std::vector<Production>>(Symbol("E",START),rhs));
//
//    rhs.clear();
//    symbols.clear();
//    symbols.push_back(Symbol("+",TERMINAL));
//    symbols.push_back(Symbol("T",NON_TERMINAL));
//    symbols.push_back(Symbol("E`",NON_TERMINAL));
//    rhs.push_back(Production(symbols));
//    symbols.clear();
//    symbols.push_back(Symbol(EPSILONSYMBOl,EPSILON));
//    rhs.push_back(Production(symbols));
//    grammar->productions.insert(std::pair<Symbol,std::vector<Production>>(Symbol("E`",NON_TERMINAL),rhs));
//
//    rhs.clear();
//    symbols.clear();
//    symbols.push_back(Symbol("F",NON_TERMINAL));
//    symbols.push_back(Symbol("T`",NON_TERMINAL));
//    rhs.push_back(Production(symbols));;
//    grammar->productions.insert(std::pair<Symbol,std::vector<Production>>(Symbol("T",NON_TERMINAL),rhs));
//
//
//    rhs.clear();
//    symbols.clear();
//    symbols.push_back(Symbol("*",TERMINAL));
//    symbols.push_back(Symbol("F",NON_TERMINAL));
//    symbols.push_back(Symbol("T`",NON_TERMINAL));
//    rhs.push_back(Production(symbols));
//    symbols.clear();
//    symbols.push_back(Symbol(EPSILONSYMBOl,EPSILON));
//    rhs.push_back(Production(symbols));
//    grammar->productions.insert(std::pair<Symbol,std::vector<Production>>(Symbol("T`",NON_TERMINAL),rhs));
//
//
//    rhs.clear();
//    symbols.clear();
//    symbols.push_back(Symbol("(",TERMINAL));
//    symbols.push_back(Symbol("E",START));
//    symbols.push_back(Symbol(")",TERMINAL));
//    rhs.push_back(Production(symbols));
//    symbols.clear();
//    symbols.push_back(Symbol("id",TERMINAL));
//    rhs.push_back(Production(symbols));
//    grammar->productions.insert(std::pair<Symbol,std::vector<Production>>(Symbol("F",NON_TERMINAL),rhs));
//
//    std::set<Symbol>first ;
//    first.insert(Symbol("(",TERMINAL));
//    first.insert(Symbol("id",TERMINAL));
//    grammar->first.insert(std::pair<Symbol,std::set<Symbol>>(Symbol("F",NON_TERMINAL),first));
//
//    first.clear();
//    first.insert(Symbol("*",TERMINAL));
//    first.insert(Symbol(EPSILONSYMBOl,EPSILON));
//    grammar->first.insert(std::pair<Symbol,std::set<Symbol>>(Symbol("T`",NON_TERMINAL),first));
//
//    first.clear();
//    first.insert(Symbol("(",TERMINAL));
//    first.insert(Symbol("id",TERMINAL));
//    grammar->first.insert(std::pair<Symbol,std::set<Symbol>>(Symbol("T",NON_TERMINAL),first));
//
//    first.clear();
//    first.insert(Symbol("(",TERMINAL));
//    first.insert(Symbol("id",TERMINAL));
//    grammar->first.insert(std::pair<Symbol,std::set<Symbol>>(Symbol("E",START),first));
//
//    first.clear();
//    first.insert(Symbol("+",TERMINAL));
//    first.insert(Symbol(EPSILONSYMBOl,EPSILON));
//    grammar->first.insert(std::pair<Symbol,std::set<Symbol>>(Symbol("E`",NON_TERMINAL),first));
//
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
