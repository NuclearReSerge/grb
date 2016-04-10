#include <exception>
#include <string>

#pragma once

namespace grb
{


namespace type
{
enum ExceptionLevel
{
  EXCEPTION_CRITICAL,
  EXCEPTION_HIGH,
  EXCEPTION_WARNING,
  EXCEPTION_LOW,
  // last
  EXCEPTION_LEVEL_UNKNOWN
};
}
#define INCLUDE_FUNCTION_IN_EXC

#ifdef INCLUDE_FUNCTION_IN_EXC
  #define PRETTY_FUNCTION __PRETTY_FUNCTION__
#else
  #define PRETTY_FUNCTION ""
#endif

class Exception : public std::exception
{
public:
  Exception(type::ExceptionLevel level = type::EXCEPTION_LEVEL_UNKNOWN,
            const std::string& message = "",
            const std::string& function = "");
  const char* what() const noexcept;
  type::ExceptionLevel getLevel() const;

  static const std::string& getPrefix();
private:
  static const std::string _prefix;
  std::string _message;
  type::ExceptionLevel _level;
};

}
