#include "Parser.h"

void Parser::parse(ParsingTable *parsingTable, Tokenizer *tokenizer, FileWriter *writer) {
    initialize(parsingTable);

    ParseResult result(true);
    std::string token;
    while (tokenizer->hasTokens()) {
        if (result.tokenDone) {
            token = tokenizer->nextToken();
        }
        if (tokenizer->tokenFound()) {
            Symbol symbol;
            symbol.name = token;
            result = Parser::getInstance().parse(symbol);
            writer->writeParserResult(result);
        }
    }

    while (!Parser::getInstance().isDone()) {
        Symbol endSymbol = Symbol(END, START);
        result = Parser::getInstance().parse(endSymbol);
        writer->writeParserResult(result);
    }
}

ParseResult Parser::parse(Symbol token) {
    std::cout << "\t\t\t" << token.toString() << std::endl;
    Symbol top = stack->top();
    ParseResult result(false);
    if (top.type == START && token.type == START) {
        result.msg = "FINISHED MATCHING";
        stack->pop();
    } else if (top.type == EPSILON) {
        result.msg = "SKIP";
        stack->pop();
    } else if (top.type == SymbolType::TERMINAL) {
        if (top.name != token.name) {
            result.msg = "Error: missing " + top.name + ", inserted";
        } else {
            result.msg = "Matched " + token.name;
            result.tokenDone = true;
        }
        stack->pop();
    } else {
        if (parseTable->isEmpty(top, token)) {
            result.msg = "Error: (illegal " + top.name + ") - discard " + token.name;
            result.tokenDone = true;
        } else if (parseTable->isSync(top, token)) {
            result.msg = "Error: Looking for a synchronizing token";
            stack->pop();
        } else {
            Production prod = parseTable->getProduction(top, token);
            result.rule.first = stack->top();
            result.rule.second = prod;
            stack->pop();
            for (std::vector<Symbol>::reverse_iterator it = prod.production.rbegin();
                 it != prod.production.rend(); it++) {
                stack->push(*it);
            }
        }
    }
    return result;
}


void Parser::initialize(ParsingTable *table) {
    parseTable = table;
    stack = new std::stack<Symbol>();
    stack->push(Symbol(END, SymbolType::START));
    stack->push(table->getStartSymbol());
}

bool Parser::isDone() {
    return stack->empty();
}

void Parser::printStack() {
    std::stack<Symbol> tmp;
    while (!stack->empty()) {
        Symbol symbol = stack->top();
        tmp.push(symbol);
        stack->pop();
    }
    while (!tmp.empty()) {
        Symbol symbol = tmp.top();
        std::cout << tmp.top().toString() << ", ";
        stack->push(symbol);
        tmp.pop();
    }
}
