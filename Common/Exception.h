#include <exception>
#include <string>

#pragma once

namespace grb
{


namespace type
{
enum ExceptionLevel
{
  EXCEPTION_CRITICAL      = 0x00,
  EXCEPTION_HIGH          = 0x01,
  EXCEPTION_WARNING       = 0x02,
  EXCEPTION_LOW           = 0x03,
//EXCEPTION_              = 0x0E,
  EXCEPTION_MASK          = 0x0F,
  // MODIFIERS
  EXCEPTION_MOD_NO_PREFIX = 0x10,
//EXCEPTION_MOD_            0x20,
//EXCEPTION_MOD_            0x40,
//EXCEPTION_MOD_            0x80,
  // LAST
  EXCEPTION_LEVEL_UNKNOWN = 0xFF
};
}
//#define INCLUDE_FUNCTION_IN_EXC

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
