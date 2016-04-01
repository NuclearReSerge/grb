#include "Data/CatalogEntry.h"

#include <map>
#include <string>
#include <vector>

#pragma once

namespace grb
{

extern const std::string NAME_NA;

class NameMapper
{
public:
  NameMapper() = delete;
  NameMapper(const type::ColumnType columnType);
  virtual ~NameMapper();

  bool isPresent(const std::string& name) const;
  type::Index getIndex(const std::string& name) const;
  const std::string& getName(const type::Index& index) const;
  const std::string& getColumnName() const;
  const std::string& getDescription() const;

protected:
  virtual std::vector<std::string>& getNameList() const = 0;
  void initiate();

  std::map<std::string, type::Index> _map;
  const type::ColumnType _columnType;
  std::string& _description;
};

}
