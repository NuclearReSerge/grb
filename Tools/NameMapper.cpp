#include "Tools/NameMapper.h"

#include "Data/ColumnMapper.h"
#include <sstream>

namespace grb
{
namespace mapper
{

type::Index
NameMapper::getIndex(const std::string& name) const  throw(Exception)
{
  try
  {
    return getValue(name);
  }
  catch (Exception& baseExc)
  {
    std::stringstream ss;
    ss << "NameMapper type=" << _columnType
       << " [" << grb::ColumnMapper::instance()->getKey(_columnType) << "].";
    ss << std::endl << baseExc.what();
    Exception exc(baseExc.getLevel(), ss.str().c_str(), PRETTY_FUNCTION);
    throw exc;
  }
}

const std::string&
NameMapper::getName(const type::Index& index) const  throw(Exception)
{
  try
  {
    return getKey(index);
  }
  catch (Exception& baseExc)
  {
    std::stringstream ss;
    ss << "NameMapper type=" << _columnType
       << " [" << grb::ColumnMapper::instance()->getKey(_columnType) << "].";
    ss << std::endl << baseExc.what();
    Exception exc(baseExc.getLevel(), ss.str().c_str(), PRETTY_FUNCTION);
    throw exc;
  }
}

} // namespace mapper
} // namespace grb
