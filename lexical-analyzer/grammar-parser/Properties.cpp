#include "Properties.hpp"

std::istream &Properties::operator>>(std::istream &inStream,
                                     PropertiesData &prop) {
  std::string str, key, value;
  while (std::getline(inStream, str)) {
    std::string::size_type begin = str.find_first_not_of(" \f\t\v");
    if (!isSkipLine(str, begin)) {
      std::string::size_type end = str.find('=', begin);
      key = str.substr(begin, end - begin);
      key.erase(key.find_last_not_of(" \f\t\v") + 1);
      if (!key.empty()) {
        begin = str.find_first_not_of(" \f\n\r\t\v", end + 1);
        end = str.find_last_not_of(" \f\n\r\t\v") + 1;
        value = str.substr(begin, end - begin);
      }
      prop[key] = value;
    }
  }
  return inStream;
}

std::ostream &Properties::operator<<(std::ostream &outStream,
                                     const PropertiesData &prop) {
  PropertiesData::const_iterator iter;
  for (iter = prop.begin(); iter != prop.end(); iter++)
    outStream << iter->first << " = " << iter->second << std::endl;
  return outStream;
}

bool Properties::PropertiesData::iskey(const std::string &s) const {
  return count(s) != 0;
}

bool Properties::isSkipLine(std::string str, std::string::size_type begin) {
  return begin == std::string::npos ||
         std::string("#;").find(str[begin]) != std::string::npos;
}
