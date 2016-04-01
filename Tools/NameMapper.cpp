#include "Tools/NameMapper.h"

#include <algorithm>

namespace grb
{

const std::string NAME_NA = "N/A";

namespace
{
  std::string DESCRIPTION;
}

NameMapper::NameMapper(const type::ColumnType columnType)
  : _columnType(columnType), _description(DESCRIPTION)
{
}

NameMapper::~NameMapper()
{
  _map.clear();
}

void NameMapper::initiate()
{
  type::Index i = 0;
  for (std::string& name : getNameList())
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
NameMapper::getIndex(const std::string& name) const
{
  try
  {
    return _map.at(name);
  }
  catch (std::out_of_range& exc)
  {
    return -1;
  }
}

const std::string&
NameMapper::getName(const type::Index& index) const
{
  auto iter = std::find_if(_map.begin(), _map.end(),
                [index](const std::pair<const std::string, type::Index>& item)
                { return item.second == index; });
  if (iter == _map.end())
    return NAME_NA;

  return iter->first;
}

const std::string&
NameMapper::getColumnName() const
{
  return GlobalName::getColumn(_columnType);
}

const std::string&
NameMapper::getDescription() const
{
  return _description;
}

} // namespace grb
