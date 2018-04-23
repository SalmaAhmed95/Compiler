//
// Created by salma on 21/03/18.
//

#include <cmath>
#include "FileWriter.h"

FileWriter::FileWriter() {
    fileName = DEFAULT_OUTPUT;
    file.open(fileName);
}

FileWriter::FileWriter(std::string fileName) {
    fileName = fileName;
    file.open(fileName);

}

void FileWriter::writeMatch(std::string match, std::string tokenClass) {
    file << "Token: " << match;
    fillSpaces(SPACING - match.length());
    file << "Token Class: " << tokenClass << "\n";
}

void FileWriter::writeError(std::string error) {
    file << error << "\n";
}

void FileWriter::writeTransitionTable(DFA *dfaMin) {
    stateID stateNum = dfaMin->getNumberOfStates();
    std::set<char> attributes = dfaMin->getAllAttributes();
    fillSpaces(attributes.size() * 2);
    file << "Minimized Transition Table" << "\n";
    drawLine(attributes.size() * 4 + 12);
    fillSpaces(15);
    for (auto attr : attributes) {
        file << attr;
        fillSpaces(3);
    }
    file << "\n";
    drawLine(attributes.size() * 4 + 12);
    for (int i = 0; i < stateNum; i++) {
        file << "\n" << i;
        std::string s = std::to_string(i);
        fillSpaces(4 - s.length());
        if (i == 0) {
            file << "Start";
            fillSpaces(5);
        } else if (dfaMin->isPHI(i)) {
            file << "Phi";
            fillSpaces(7);
        } else {
            file << dfaMin->getTokenClass(i);
            fillSpaces(10 - dfaMin->getTokenClass(i).length());
        }
        file << "|";
        for (auto attr : attributes) {
            std::vector<stateID> nextState = dfaMin->getTransitions(i, attr);
            if (nextState.size() == 0)
                fillSpaces(4);
            else {
                file << nextState[0];
                std::string s = std::to_string(nextState[0]);
                fillSpaces(4 - s.length());
            }
        }
    }
    file << "\n";
    drawLine(attributes.size() * 4 + 12);
}

void FileWriter::closeFile() {
    file.close();
}

void FileWriter::fillSpaces(int spaceNum) {
    for (int i = 0; i < spaceNum; i++)
        file << " ";
}

void FileWriter::drawLine(int length) {
    for (int i = 0; i < length; i++)
        file << "-";
    file << "\n";


}

void FileWriter::writeParserResult(std::pair<std::pair<Symbol, Production>, std::string> parserResult) {
    if (parserResult.second.empty()) {
        file << parserResult.first.first.toString() << " --> " << parserResult.first.second.toString() << std::endl;
    }
}
