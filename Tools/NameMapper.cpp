#include "Tools/NameMapper.h"

#include "Common/GlobalName.h"

#include <sstream>
#include <algorithm>

namespace grb
{

NameMapper::NameMapper(const type::ColumnType columnType, const std::string& description)
  : _columnType(columnType), _description(description)
{
}

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
    ss << "NameMapper type=" << _columnType << " [" << GlobalName::getColumn(_columnType) << "].";
    ss << std::endl << baseExc.what();
    Exception exc(baseExc.getLevel(), ss.str(), PRETTY_FUNCTION);
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
    ss << "NameMapper type=" << _columnType << " [" << GlobalName::getColumn(_columnType) << "].";
    ss << std::endl << baseExc.what();
    Exception exc(baseExc.getLevel(), ss.str(), PRETTY_FUNCTION);
    throw exc;
  }
}

type::ColumnType
NameMapper::getColumnType() const
{
  return _columnType;
}

const std::string&
NameMapper::getDescription() const
{
  return _description;
}

}
