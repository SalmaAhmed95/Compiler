#include <stack>
#include "Parser.h"

std::pair<Production, std::string> Parser::parse(Symbol *token) {
    Symbol *top = &(stack->top());
    std::pair<Production, std::string> *result = new std::pair<Production, std::string>;
    if (top->type == SymbolType::TERMINAL) {
        if (top->name != token->name) {
            result->second = "Error: missing " + top->name + ", inserted";
        }
        stack->pop();
    } else {
        if (parseTable->isEmpty(top, token)) {
            result->second = "Error: (illegal " + top->name + ") - discard " + token->name;
        } else if (parseTable->isSync(top, token)) {
            result->second = "Error: Looking for a synchronizing token";
            stack->pop();
        } else {
            Production prod = parseTable->getProduction(top, token);
            stack->pop();
            for (int i = prod.production.size() - 1; i >= 0; i--) {
                stack.push(prod.production[i]);
            }
            result->first = prod;
            result->second = "";
        }
    }
    return &reult;
}


void Parser::initialize(ParseTable parseTable) {
    Parser::parseTable = parseTable;
    stack = new std::stack<Symbol>();
    stack->push(Symbol("$", SymbolType::START));
}