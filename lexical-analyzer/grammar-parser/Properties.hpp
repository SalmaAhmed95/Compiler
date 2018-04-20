#ifndef COMPILER_PROPERTIES_H
#define COMPILER_PROPERTIES_H

#include <fstream>
#include <iostream>
#include <map>
#include <string>

namespace Properties {

/* The Bundle the holds the properties in a key-value manner */
struct PropertiesData : std::map<std::string, std::string> {
  bool iskey(const std::string &s) const;
};

/* Operator overloading for ">>" to read the data from the properties file. */
std::istream &operator>>(std::istream &inStream, PropertiesData &prop);

/* Operator overloading for "<<" to write the properties loaded. */
std::ostream &operator<<(std::ostream &outStream, const PropertiesData &prop);

/* Checks that the current read line is a line that should be skipped. */
bool isSkipLine(std::string str, std::string::size_type begin);
}

#endif //COMPILER_PROPERTIES_H