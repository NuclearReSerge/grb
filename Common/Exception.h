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

} // namespace

#ifdef INCLUDE_FUNCTION_IN_EXC
  #define PRETTY_FUNCTION __PRETTY_FUNCTION__
#else
  #define PRETTY_FUNCTION ""
#endif

class Exception : public std::exception
{
public:
  Exception(uint8_t level,
            std::string message = "",
            std::string function = "");

  Exception(type::ExceptionLevel level = type::EXCEPTION_LEVEL_UNKNOWN,
            std::string message = "",
            std::string function = "");

  const char* what() const noexcept
  {
    return _message.c_str();
  }

  type::ExceptionLevel getLevel() const
  {
    return (type::ExceptionLevel) (_level & type::EXCEPTION_MASK);
  }

  static const std::string& getPrefix();

private:
  type::ExceptionLevel _level;
  std::string _message;
};

}
