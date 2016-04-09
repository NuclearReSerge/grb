#include "Common/Global.h"

#include <string>
#include <vector>

#pragma once

namespace grb
{

class GlobalName
{
public:
  GlobalName() = delete;
  GlobalName(const GlobalName& ) = delete;
  GlobalName& operator= (const GlobalName&) = delete;

  static std::string& getDatabaseTable(type::DatabaseTableType dbType);
  static std::string& getCatalog(type::CatalogType catType);
  static std::string& getColumn(type::ColumnType columnType);
  static std::string& getColumnDescription(type::ColumnType columnType);
  static std::string& getValue(type::ValueType valueType);
  static std::string& getUnit(type::UnitType unitType);
  static std::string& getCoordinateSystem(type::CoordinateSystemType coordinateSystemType);

private:
  static std::string& getWithRangeCheck(std::vector<std::string>& nameList, std::size_t index);
};

}
