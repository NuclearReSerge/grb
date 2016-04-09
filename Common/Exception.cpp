#include "Common/Exception.h"

namespace grb
{

const std::string Exception::_prefix = "GRB exception: ";

Exception::Exception(const std::string& message, const std::string& function)
{
  _message = _prefix;
  if (!function.empty())
  {
    _message += "[" + function + "] ";
  }
  _message += message;
}

const std::string& Exception::getPrefix()
{
  return _prefix;
}

const char*
Exception::what() const noexcept
{
  return _message.c_str();
}

}
