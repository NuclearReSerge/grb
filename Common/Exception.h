#include <exception>
#include <string>

#pragma once

namespace grb
{

#ifdef INCLUDE_FUNCTION_IN_EXC
  #define PRETTY_FUNCTION __PRETTY_FUNCTION__
#else
  #define PRETTY_FUNCTION ""
#endif

class Exception : public std::exception
{
public:
  Exception(const std::string& message = "", const std::string& function = "");
  const char* what() const noexcept;

  static std::string getPrefix();
private:
  static std::string _prefix;
  std::string _message;
};

}
