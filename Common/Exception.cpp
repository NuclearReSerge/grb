#include "Common/Exception.h"

#include <string>

static const std::string _prefix = "GRB exception: ";

namespace grb
{

Exception::Exception(type::ExceptionLevel level, std::string message, std::string function)
  : _level(level), _message("")
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

const std::string&
Exception::getPrefix()
{
  return _prefix;
}

} // namespace grb
