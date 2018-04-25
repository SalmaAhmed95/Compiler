#include "Parser.h"

void Parser::parse(ParsingTable *parsingTable, Tokenizer *tokenizer, FileWriter *writer) {
    initialize(parsingTable);

    std::string token;
    ParseResult result;
    result.tokenDone = true;

    // There are more tokens or no more tokens but the last one is not done yet
    while (tokenizer->hasTokens() || !result.tokenDone) {
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

    // For the remaining elements in the stack with the END symbol
    while (!stack->empty()) {
        result = Parser::getInstance().parse(END_SYMBOL);
        writer->writeParserResult(result);
    }
}

ParseResult Parser::parse(Symbol token) {
    // To remove all the epsilons then start matching another symbol so the output message will not be empty
    while (stack->top().type == EPSILON) { stack->pop(); }

    Symbol top = stack->top();
    ParseResult result;
    if (top.type == START && token.type == START) {
        stack->pop();
        result.msg = "FINISHED MATCHING";
        result.tokenDone = true;
    } else if (top.type == SymbolType::TERMINAL) {
        if (top.name != token.name) {
            result.msg = "Error: missing " + top.toString() + ", inserted";
            result.tokenDone = false;
        } else {
            result.msg = "Matched " + token.toString();
            result.tokenDone = true;
        }
        stack->pop();
    } else {
        if (parseTable->isEmpty(top, token)) {
            result.msg = "Error: (illegal " + top.toString() + ") - discard " + token.toString();
            result.tokenDone = true;
        } else if (parseTable->isSync(top, token)) {
            result.msg = "Error: Looking for a synchronizing token";
            result.tokenDone = false;
            stack->pop();
        } else {
            Production prod = parseTable->getProduction(top, token);
            result.rule.first = stack->top();
            result.rule.second = prod;
            result.tokenDone = false;
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
