#include "Common/Exception.h"

#include <string>

static std::string _prefix = "GRB exception: ";
static std::string _message = "";

namespace grb
{

Exception::Exception(type::ExceptionLevel level, const char* message, const char* function)
  : _level(level)
{
  if (!(_level & type::EXCEPTION_MOD_NO_PREFIX))
  {
    _message = _prefix;
  }
  if (function)
  {
    _message += "[";
    _message += function;
    _message += "] ";
  }
  _message += message;
}


const char*
Exception::what() const noexcept
{
  return _message.c_str();
}

type::ExceptionLevel
Exception::getLevel() const
{
  return (type::ExceptionLevel) (_level & type::EXCEPTION_MASK);
}

const char*
Exception::getPrefix()
{
  return _prefix.c_str();
}

} // namespace grb
