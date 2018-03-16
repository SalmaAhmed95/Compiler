#include <string>

class Token {
public:
  Token();
  Token(std::string type, std::string postfixRegex, int priority);
  virtual ~Token();
  int getPriority();
  std::string getPostfixRegix();
  std::string getType();
  void setPriority(int priority);
  void setPostfixRegex(std::string postfixRegex);
  void setType(std::string type);

private:
  std::string postfixRegex;
  std::string type;
  int priority;
};
