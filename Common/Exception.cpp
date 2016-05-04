#include "Common/Exception.h"

namespace grb
{

const std::string Exception::_prefix = "GRB exception: ";

Exception::Exception(type::ExceptionLevel level, const std::string& message,
                     const std::string& function)
  : _level(level)
{
  if (!(_level & type::EXCEPTION_MOD_NO_PREFIX))
  {
    _message = _prefix;
  }
  if (!function.empty())
  {
    _message += "[" + function + "] ";
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

const std::string& Exception::getPrefix()
{
  return _prefix;
}


}
