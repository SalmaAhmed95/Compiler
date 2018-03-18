//
// Created by salma on 18/03/18.
//

#ifndef COMPILER_ERRORHANDLER_H
#define COMPILER_ERRORHANDLER_H

#include <string>

class ErrorHandler {
private:
    enum Error {
        lexicalError

    };
    static const std::string errors[];
};


#endif //COMPILER_ERRORHANDLER_H
