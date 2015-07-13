#ifndef SYNTAX_ERROR_H_
#define SYNTAX_ERROR_H_
#include <stdexcept>

//This is from Professor Kuhail's Stack Application folder
class Syntax_Error : public std::invalid_argument {
  public:
    Syntax_Error(std::string msg) : std::invalid_argument(msg) {}
};
#endif
