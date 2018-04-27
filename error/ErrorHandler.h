//
// Created by salma on 18/03/18.
//

#ifndef COMPILER_ERRORHANDLER_H
#define COMPILER_ERRORHANDLER_H

#include <string>

class ErrorHandler {
public:

    enum Error {
        lexicalError,
        NONTERMINAL_INVALID,
        MULTIPLE_DEFINITIONS,
        MISSING_START_SYMBOL,
        MISSING_NONTERMINAL_DEFINITION,
        ERROR_IN_TERMINAL_DEFINTIION,
        NOSPACE_BEFORE_LAMBDA,
        notLL1Error

    };
    static const std::string errors[];
};

#endif // COMPILER_ERRORHANDLER_H
