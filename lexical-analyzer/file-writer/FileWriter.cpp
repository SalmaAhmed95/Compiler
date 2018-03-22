//
// Created by salma on 21/03/18.
//

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

void FileWriter::closeFile() {
    file.close();
}

void FileWriter::fillSpaces(int spaceNum) {
    for (int i = 0; i < spaceNum; i++)
        file << " ";
}