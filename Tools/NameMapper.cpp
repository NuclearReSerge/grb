#include "Tools/NameMapper.h"

#include <sstream>
#include <algorithm>

namespace grb
{

NameMapper::NameMapper(const type::ColumnType columnType, const std::string& description)
  : _columnType(columnType), _description(description)
{
}

NameMapper::~NameMapper()
{
  _map.clear();
}

void NameMapper::initiate()
{
  type::Index i = 0;
  for (const std::string& name : getNameList())
  {
    _map.insert({name, i++});
  }
}

bool
NameMapper::isPresent(const std::string& name) const
{
  return _map.find(name) != _map.end();
}

type::Index
NameMapper::getIndex(const std::string& name) const  throw(Exception)
{
  try
  {
    return _map.at(name);
  }
  catch (std::out_of_range& sysExc)
  {
    std::stringstream ss;
    ss << "NameMapper did not find index for name=" << name << " in column type=" << _columnType
       << " [" << GlobalName::getColumn(_columnType) << "], exc.what()=" << sysExc.what();
    Exception exc(ss.str(), PRETTY_FUNCTION);
    throw exc;
  }
}

const std::string&
NameMapper::getName(const type::Index& index) const  throw(Exception)
{
  const auto iter = std::find_if(_map.begin(), _map.end(),
                [index](const std::pair<std::string, type::Index>& item)
                { return item.second == index; });
  if (iter == _map.end())
  {
    std::stringstream ss;
    ss << "NameMapper did not find name for index=" << index << " in column type=" << _columnType
       << " [" << GlobalName::getColumn(_columnType) << "]";
    Exception exc(ss.str(), PRETTY_FUNCTION);
    throw exc;
  }

  return iter->first;
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
