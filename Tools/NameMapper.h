#include "Common/Exception.h"
#include "Common/Global.h"

#include <map>
#include <string>
#include <vector>

#pragma once

namespace grb
{

class NameMapper
{
public:
  NameMapper() = delete;
  NameMapper(const type::ColumnType columnType, const std::string& description);
  virtual ~NameMapper();

  bool isPresent(const std::string& name) const;
  type::Index getIndex(const std::string& name) const throw(Exception);
  const std::string& getName(const type::Index& index) const throw(Exception);
  type::ColumnType getColumnType() const;
  const std::string& getDescription() const;

protected:
  virtual const std::vector<std::string>& getNameList() const = 0;
  void initiate();

  std::map<std::string, type::Index> _map;
  const type::ColumnType _columnType;
  const std::string& _description;

};

}
