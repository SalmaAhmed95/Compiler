//
// Created by salma on 21/03/18.
//

#ifndef COMPILER_FILEWRITER_H
#define COMPILER_FILEWRITER_H

#include <string>
#include <iostream>
#include <fstream>
#include "../automata/DFA.h"
#include "../../parser/CFGParser.h"

#define  DEFAULT_OUTPUT "output.txt"
#define  SPACING 20

class FileWriter {
public:
    FileWriter();

    FileWriter(std::string fileName);

    void writeMatch(std::string match, std::string tokenClass);

    void writeError(std::string error);

    void closeFile();

    void writeTransitionTable(DFA* dfaMin);

    void writeParserResult(std::pair<std::pair<Symbol, Production>, std::string> parserResult);

private:
    std::ofstream file;
    std::string fileName;

    void fillSpaces(int spaceNum);
    void drawLine (int length);
};


#endif //COMPILER_FILEWRITER_H