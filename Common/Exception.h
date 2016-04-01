#include <exception>
#include <string>

#pragma once

namespace grb
{

#define INCLUDE_FUNCTION_IN_EXC

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

  static const std::string& getPrefix();
private:
  static const std::string _prefix;
  std::string _message;
};

}
