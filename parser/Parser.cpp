#include "Parser.h"

void Parser::parse(ParsingTable *parsingTable,
                   Tokenizer *tokenizer,
                   FileWriter *parserWriter,
                   FileWriter *leftDerivationWriter) {

    initialize(parsingTable);
    parserWriter->writeParsingTable(parsingTable);

    Lexeme token;

    ParseResult result;
    result.tokenDone = true;

    leftDerivationWriter->writeLeftDerivation(derivativeLeftSide, stack, "");

    // There are more tokens or no more tokens but the last one is not done yet
    while (tokenizer->hasTokens() || !result.tokenDone) {
        if (result.tokenDone) {
            token = tokenizer->nextToken();
        }
        if (tokenizer->tokenFound()) {
            result = Parser::getInstance().parse(token);
            parserWriter->writeParserResult(result);
            if (!result.tokenDone || (result.tokenDone && token.name != token.lexemeType) || !result.msg.empty()) {
                leftDerivationWriter->writeLeftDerivation(derivativeLeftSide, stack, result.msg);
            }
        }
    }

    // For the remaining elements in the stack with the END symbol
    while (!stack->empty()) {
        result = Parser::getInstance().parse(END_LEXEME);
        parserWriter->writeParserResult(result);
        leftDerivationWriter->writeLeftDerivation(derivativeLeftSide, stack, result.msg);
        if (!stack->empty()) {
            stack->pop_front();
        }
    }
}

ParseResult Parser::parse(Lexeme token) {
    // To remove all the epsilons then start matching another symbol so the output message will not be empty
    while (stack->front().type == EPSILON) { stack->pop_front(); }

    Symbol top = stack->front();
    ParseResult result;
    if (top.type == START && token == END_LEXEME) {
        stack->pop_front();
        result.msg = "FINISHED MATCHING";
        result.tokenDone = true;
    } else if (top.type == SymbolType::TERMINAL) {
        if (top.name != token.lexemeType) {
            return panicModeRecovery(token, UNMATCHED_TERMINALS);
        } else {
            result.msg = "Matched " + token.name;
            result.tokenDone = true;
            derivativeLeftSide->push_back(Symbol(token.name, TERMINAL));
            stack->pop_front();
        }
    } else {
        if (parseTable->isEmpty(top, Symbol(token.lexemeType, TERMINAL))) {
            return panicModeRecovery(token, EMPTY_CELL);
        } else if (parseTable->isSync(top, Symbol(token.lexemeType, TERMINAL))) {
            return panicModeRecovery(token, SYNC_CELL);
        } else {
            Production prod = parseTable->getProduction(top, Symbol(token.lexemeType, TERMINAL));
            result.rule.first = stack->front();
            result.rule.second = prod;
            result.tokenDone = false;
            stack->pop_front();
            for (auto it = prod.production.rbegin(); it != prod.production.rend(); it++) {
                stack->push_front(*it);
            }
        }
    }
    return result;
}


void Parser::initialize(ParsingTable *table) {
    parseTable = table;
    if (stack != nullptr) {
        delete (stack);
        delete (derivativeLeftSide);
    }
    stack = new std::list<Symbol>();
    derivativeLeftSide = new std::list<Symbol>();
    stack->push_front(Symbol(END, SymbolType::START));
    stack->push_front(table->getStartSymbol());
}

ParseResult Parser::panicModeRecovery(Lexeme token, Parser::ERROR error) {
    ParseResult result;
    switch (error) {
        case UNMATCHED_TERMINALS:
            result.msg = "Error: missing " + stack->front().toString() + ", inserted";
            result.tokenDone = false;
            stack->pop_front();
            break;
        case EMPTY_CELL:
            result.msg = "Error: (illegal " + stack->front().toString() + ") - discard " + token.name;
            result.tokenDone = true;
            break;
        case SYNC_CELL:
            result.msg = "SYNC";
            result.tokenDone = false;
            stack->pop_front();
            break;
    }
    return result;
}
